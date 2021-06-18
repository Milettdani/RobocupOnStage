import time
import colorama
from colorama import Fore, Back, Style

colorama.init()

start_time = 0
def init():
    start_time = time.time()

def command():
    print(Fore.CYAN, end='')
    print(timer(5), end=' > ')
    print(Fore.RESET, end='')
    inp = input()
    return inp
    
def log(data):
    print(Fore.WHITE, end='')
    print(timer(7), end=' ')
    print(data, end='')
    print(Fore.RESET)

def info(data):
    print(Fore.GREEN, end='')
    print(timer(7), end=' ')
    print(data, end='')
    print(Fore.RESET)

def warning(data):
    print(Fore.YELLOW, end='')
    print(timer(7), end=' ')
    print(data, end='')
    print(Fore.RESET)

def error(data):
    print(Fore.RED, end='')
    print(timer(7), end=' ')
    print(data, end='')
    print(Fore.RESET)

def timer(length):
    return str(time.time() - start_time)[:length].ljust(length, '0')
