#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, time, logging
logging.basicConfig(level=logging.INFO)

sys.path.append('../')
from obswebsocket import obsws, requests  # noqa: E402

SERVER_HOST = "localhost"
SERVER_PORT = 4444
SERVER_PASS = "secret"
DELAY_TIME = 60 / 120

SCENES = {'PianoTitleScene': 1, 'DrumTitleScene': 1, 'PianoScene': 3, 'DrumScene': 3}
TITLES = ['ALMA', 'KÖRTE', 'RÉPA', 'PIROS', 'KÉK', 'ZÖLD', 'NEM']

DEBUG_MODE = True

if __name__ == '__main__':
    server = obsws(SERVER_HOST, SERVER_PORT, SERVER_PASS)
    server.connect()
    with open('TitleSceneText.txt', 'w') as text_file:
        text_file.write(TITLES[0])
        

    time.sleep(2)
    
    try:
        for title_index, title in enumerate(TITLES):
            print(title, end=' ')
            with open('TitleSceneText.txt', 'w') as text_file:
                text_file.write(title)
                
            for scene_index, scene in enumerate(SCENES):
                server.call(requests.SetCurrentScene(scene))
                if scene_index == 2 and title != TITLES[-1]:
                    with open('TitleSceneText.txt', 'w') as text_file:
                        text_file.write(TITLES[title_index + 1])
                for _ in range(SCENES[scene]):
                    print(f"Switching to {scene}")
                    time.sleep(DELAY_TIME * 2)

    except KeyboardInterrupt:
        pass
    finally:
        server.disconnect()
