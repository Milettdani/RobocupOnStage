import time, serial, struct
from obswebsocket import obsws, requests

SERVER_HOST = "localhost"
SERVER_PORT = 4444
SERVER_PASS = "12345678"
DELAY_TIME = 60 / 120

TEXTFILE_NAME = 'TextFile.txt'
NUMBERS = ['Number4', 'Number3', 'Number2', 'Number1']
SCENES = ['PianoTitleScene', 'DrumTitleScene',
          'PianoScene', 'PianoScene', 'PianoScene',
          'DrumScene', 'DrumScene', 'DrumScene']
TITLES = ['Ecuador', 'Pijanoo',
          'Zombie Nation']



class Controller:
    def __init__(self):
        print('INIT')
        self.connections = {'P': 0, 'D': 0, 'C': 0}
        self.isPlaying = False
        self.start_time = 0



    def connect(self):
        print('CONNECT')
        self.server = obsws(SERVER_HOST, SERVER_PORT, SERVER_PASS)
        self.server.connect()
        self.server.call(requests.SetCurrentScene('StartScene'))
        with open(TEXTFILE_NAME, 'w') as text_file:
            text_file.write(TITLES[0])
        for i in range(1, 10):
            try:
                connection = serial.Serial(port='COM' + str(i), baudrate=115200, timeout=0.1)

                print(f'Connection found on {connection.port}', end='')
                data = ''
                while data not in self.connections.keys():
                    print('.', end='')
                    data = connection.read().decode()
                self.connections[data] = connection
                print(data)
            except:
                pass
        self.write('X', 'B'.encode())
        time.sleep(2)



        
    def disconnect(self):
        print('DISCONNECT')
        self.server.disconnect()
        for connection in self.connections.values():
            if not connection == 0:
                connection.close()

    
        
    def cancel(self):
        print('CANCEL')
        self.server.call(requests.SetCurrentScene('CancelScene'))
        self.write('X', 'B'.encode())


        
    def stop(self):
        self.server.call(requests.SetCurrentScene('StopScene'))

    

    def start(self):
        print('START')
        for i in range(1, 5):
            print(f'Counting {5-i}')
            self.server.call(requests.SetCurrentScene(NUMBERS[i-1]))
            time.sleep(DELAY_TIME*2)
        self.write('X', 'A'.encode())
        self.start_time = time.time()
        self.isPlaying = True


        
    def main(self, start_time):
        if (time.time() - start_time) >= len(TITLES) * 16:
            self.isPlaying = False
            return
        title_index = int(int(time.time() - start_time) / 16)
        title = TITLES[title_index]
        scene_index = int((time.time() - start_time) % 16 / 2)
        scene = SCENES[scene_index]
        print(scene)
        self.server.call(requests.SetCurrentScene(scene))
        if scene_index == 4 and title != TITLES[-1]:
            with open(TEXTFILE_NAME, 'w') as text_file:
                text_file.write(TITLES[title_index + 1])


    
    def write(self, slave, data):
        if slave == 'X':
            for connection in self.connections.values():
                if not connection == 0:
                    connection.write(data)
        else:
            if not self.connections[slave] == 0:
                self.connections[slave].write(data)



    def transfer(self):
        for connection in self.connections.values():
            if not connection == 0:
                while connection.in_waiting > 2:
                    connection.read()
                if connection.in_waiting == 2:
                    datA = connection.read().decode()
                    datB = connection.read()
                    print(datA)
                    print(datB)
                    if datA == 'D' and datB == b'S':
                        print('send')
                        self.write('D', b'S')
                    














































    def special(self):
        #FOR DRUM
        text_file = open("toDrums.txt", "r")
        
        data_length = int(text_file.readline())
        string = f'S{data_length}X'
        for i in range(data_length):
            string += f'{int(text_file.readline())}X'
        string += f'{float(text_file.readline())}X\n'
        self.write('D', string.encode())
        text_file.close()

        #FOR PIANO
        text_file = open("toPiano.txt", "r")
        data_length = len(text_file.readlines())
        string = 'S'
        self.write('P', f'{data_length}X'.encode())
        for i in range(data_length-1):
            data = text_file.readline()
            print(data)
            string += f'{data}X'
        self.write('P', string.encode())
        
        text_file.close()
