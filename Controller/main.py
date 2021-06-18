import controller, time, console

if __name__ == '__main__':
    console.init()
    con = controller.Controller()
    commands = {
        'connect': con.connect,
        'disconnect': con.disconnect,
        'reset': con.reset,
        'start': con.start,
        'stop': con.stop,
        'high': con.high,
        'low': con.low,
        'exit': quit}
    try:
        while True:
            try:
                inp = console.command()
                commands[inp]()
                
            except KeyError:
                console.error('MAIN > invalid key')
    except KeyboardInterrupt:
        con.disconnect()
