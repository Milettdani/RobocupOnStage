import serial, console


class Controller:
    def __init__(self):
        self.is_connected = False
        self.connections = list()
    def connect(self):
        if self.is_connected:
            console.warning('failed')
            return
        console.log('connecting...')
        for i in range(1, 100):
            try:
                connection = serial.Serial(port='COM' + str(i), baudrate=115200, timeout=0.1)
                console.log(connection.port)
                #connection.open()
                self.connections.append(connection)
            except:
                pass
        self.is_connected = True
        console.info('connected')

    def disconnect(self):
        if not self.is_connected:
            console.warning('failed')
            return
        console.log('disconnecting...')
        for connection in self.connections:
            connection.close()
        self.is_connected = False;
        console.info('disconnected')

    def reset(self):
        if not self.is_connected:
            console.warning('failed')
            return
        console.log('resetting...')
        self.write(b'R')
        console.info('resetted')

    def start(self):
        if not self.is_connected:
            console.warning('failed')
            return
        console.log('starting...')
        console.info('started')
        
    def stop(self):
        if not self.is_connected:
            console.warning('failed')
            return
        console.log('stopping...')
        console.info('stopped')

    def write(self, data):
        if not self.is_connected:
            console.warning('write failed')
            return
        console.log('writing...')
        for connection in self.connections:
            connection.write(data)
        console.info('written')

    def high(self):
        if not self.is_connected:
            console.warning('failed')
            return
        console.log('stopping...')
        self.write(b'H')
        console.info('wrote')

    def low(self):
        if not self.is_connected:
            console.warning('failed')
            return
        console.log('stopping...')
        self.write(b'L')
        console.info('stopped')
    
        
