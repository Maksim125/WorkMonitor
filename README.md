# WorkMonitor

[See demo and design process here](https://www.maxyarmak.tech/projects/work-monitor)

## About the project

Part of a simple Arduino circuit hooked up to your computer to monitor how long a light has been on, accompanied by a script that stores the data in a database, and queries it to create desktop notifications for you.

## Technologies used

    Arduino
    Python 3.7
        Win10Toast
        Pandas
        SQLite
    NodeRed

## Installation
1. Build the arduino circuit diagramed [here](https://www.maxyarmak.tech/projects/work-monitor)
2. Setup a python environment with pandas and win10toast installed
3. Hook up the arduino to a serial port on your computer, and setup a NodeRed serial monitor to call the write_seconds.py file with the port's communications as the first argument. 
   - Reccomended to have the NodeRed workspace run automatically on startup.
