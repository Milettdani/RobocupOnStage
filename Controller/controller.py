#!/usr/bin/env python
import time, serial
from obswebsocket import obsws, requests

SERVER_HOST = "localhost"
SERVER_PORT = 4444
SERVER_PASS = "12345678"
DELAY_TIME = 60 / 120

TEXTFILE_NAME = 'TextFile.txt'
BLANK_SCENE = 'Blank'
SCENES = {'PianoTitleScene': 1, 'DrumTitleScene': 1, 'PianoScene': 3, 'DrumScene': 3}
TITLES = ['ALMA', 'KÖRTE', 'RÉPA', 'PIROS', 'KÉK', 'ZÖLD', 'NEM']

class Controller:
    def __init__(self):
        self.connections = list()

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
        while True:
            inp = input('CONSOLE > ')
            if(inp == 'start'):
                self.start()
            elif(inp == 'run'):
                try:
                    self.run()
                except KeyboardInterrupt:
                    self.cancel()
            elif(inp == 'stop'):
                self.stop()
    
    def run(self):
        self.write(b'1')
        start_time, scene_time = time.time(), 0
        
        scene_time = start_time if scene_time == 0 else scene_time
        for title_index, title in enumerate(TITLES):
            print(f'TITLE_INDEX > {title}\nTITLE > {title}')        
            for scene_index, scene in enumerate(SCENES):
                self.server.call(requests.SetCurrentScene(scene))
                if scene_index == 2 and title != TITLES[-1]:
                    with open(TEXTFILE_NAME, 'w') as text_file:
                        text_file.write(TITLES[title_index + 1])
                for _ in range(SCENES[scene]):
                    scene_time += DELAY_TIME * 4
                    print(f'SCENE_INDEX > {scene_index}\nSCENE > {scene}')
                    while time.time() < scene_time:
                        pass
    
    def write(self, data):
        for connection in self.connections:
            connection.write(data)
