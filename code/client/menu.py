HELP_COMMANDS = {
    "TEST": "test connection between wi-fi module and programm",
    "MOVEMENT": "request from controller a movement menu",
    "SENSOR": "request from controller a sensor menu",
    "HELP": "shows main menu",
    "EXIT": "exit from programm"
}

def help:
    for i in HELP_COMMANDS:
        print(i, ": ", HELP_COMMANDS[i])
