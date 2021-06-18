def init():
    with open('TitleSceneText.txt', 'w') as text_file:
        text_file.write(titles[0])

def main():
    try:
        for title_index, title in enumerate(titles):
            print(title, end=' ')
            with open('TitleSceneText.txt', 'w') as text_file:
                text_file.write(title)
            
            for scene_index, scene in enumerate(scenes):
                ws.call(requests.SetCurrentScene(scene))
                if scene_index == 2:
                    with open('TitleSceneText.txt', 'w') as text_file:
                        text_file.write(titles[title_index + 1])
                for _ in range(scenes[scene]):
                    print(f"Switching to {scene}")
                    time.sleep(delay_time * 2)

    except KeyboardInterrupt:
        pass
