import time, serial
from obswebsocket import obsws, requests

SERVER_HOST = "localhost"
SERVER_PORT = 4444
SERVER_PASS = "12345678"
DELAY_TIME = 60 / 120

TEXTFILE_NAME = 'TextFile.txt'
BLANK_SCENE = 'Blank'
NUMBERS = ['Number4', 'Number3', 'Number2', 'Number1']
SCENES = ['PianoTitleScene', 'DrumTitleScene',
          'PianoScene', 'PianoScene', 'PianoScene',
          'DrumScene', 'DrumScene', 'DrumScene']
TITLES = ['ALMA', 'KÖRTE', 'RÉPA', 'PIROS', 'KÉK', 'ZÖLD', 'NEM']

class Controller:
    def __init__(self):
        self.connections = list()
        self.isPlaying = False
        self.start_time = 0

    def start(self):
        self.server = obsws(SERVER_HOST, SERVER_PORT, SERVER_PASS)
        self.server.connect()
        self.server.call(requests.SetCurrentScene(BLANK_SCENE))
        with open(TEXTFILE_NAME, 'w') as text_file:
            text_file.write(TITLES[0])
        for i in range(1, 100):
            try:
                connection = serial.Serial(port='COM' + str(i), baudrate=115200, timeout=0.1)
                #connection.open()
                self.connections.append(connection)
            except:
                pass
        print(f'START > {" ".join([connection.port for connection in self.connections])}')
        time.sleep(2)
            
    def stop(self):
        self.cancel()
        self.server.disconnect()
        for connection in self.connections:
            connection.close()
        quit()

    def cancel(self):
        self.server.call(requests.SetCurrentScene(BLANK_SCENE))
        self.write(b'2')
    def console(self):
        self.start()
        input('ENTER')
        self.startPlaying()
        try:
            while self.isPlaying:
                self.obs(self.start_time)
        except KeyboardInterrupt:
            self.stopPlaying()

    def startPlaying(self):
        for i in range(1, 5):
            print(5-i)
            self.server.call(requests.SetCurrentScene(NUMBERS[i-1]))
            time.sleep(DELAY_TIME*2)
        self.write(b'1')
        self.start_time = time.time()
        self.isPlaying = True
        
    def stopPlaying(self):
        self.isPlaying = False
        self.cancel()
    
    def obs(self, start_time):
        if (time.time() - start_time) >= len(TITLES) * 16:
            self.stopPlaying()
            return
        title_index = int(int(time.time() - start_time) / 16)
        title = TITLES[title_index]
        scene_index = int((time.time() - start_time) % 16 / 2)
        scene = SCENES[scene_index]
        self.server.call(requests.SetCurrentScene(scene))
        if scene_index == 4 and title != TITLES[-1]:
            with open(TEXTFILE_NAME, 'w') as text_file:
                text_file.write(TITLES[title_index + 1])
    
    def write(self, data):
        for connection in self.connections:
            connection.write(data)
