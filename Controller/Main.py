import Controller

if __name__ == '__main__':
    controller = Controller.Controller()
    try:
        controller.connect()
        input('Press ENTER to start...')
        controller.start()
        while controller.isPlaying:
            controller.main(controller.start_time)
            controller.transfer()
        controller.stop()
    except KeyboardInterrupt:
        controller.cancel()
    finally:
        controller.disconnect()
