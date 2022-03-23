# Work Monitor
---
Inspired by the work from home era, this project helps you track how long you spend at your desk. (See a demo of it working [here](https://www.maxyarmak.tech/workmonitor))
## Version/Dependencies

```sh
C++ (arduino)
Python 3.8.11
Pandas 1.3.1
NodeRed
Win10Toast
```
## Material Dependencies
```sh
Arduino uno
10kOhm resistor
Photoresistor
7 segment 4 digit display
```

## Feature Summary
- A simple voltage divider with a photoresistor to detect light sources
- An ardunio uno running a script that counts how long the light has been on and displays the timer to a 7 segment 4 digit display
- NodeRed to monitor the serial port that the arduino is connected to and activate the python script to record each session
    -  The script takes as its first argument the number of seconds to record, it will then use your system's date and time to log this session
-  After it has been logged, a toast is sent to your computer detailing your total time for today and the last several days

## Installation Instructions
1. Build the arduino circuit according to the specifications that can be found [here](maxyarmak.tech/workmonitor)
2. Upload to the arduino the script in the `work_monitor` directory
3. Setup NodeRed on your computer to monitor the arduino's serial port, and run the `write_seconds.py` script with the output of the serial port as its first argument. Setup instructions provided [here](https://nodered.org/docs/getting-started/windows)
    - Ideally you would want to setup the option where it activates on startup and runs in the background so you never have to remember to turn it on

(You also have the option to skip step 3, which will remove `Win10Toast` and `NodeRed` dependencies, and have the arduino run the timer without sending anything to the serial port. This will exclude the ability to run diagnostics on or log your hours, however)
