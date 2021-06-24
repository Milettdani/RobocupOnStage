import Controller

if __name__ == '__main__':
    controller = Controller.Controller()
    try:
        controller.connect()
        input('Press ENTER to start...')
        controller.start()
        while controller.isPlaying:
            controller.main(controller.start_time)
        input("special...")
        controller.special()
        input("start interact")
        controller.write('X', b'A')
        controller.stop()
        
    except KeyboardInterrupt:
        controller.cancel()
    finally:
        
        controller.disconnect()
