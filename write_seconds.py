import sys
import datetime as dt
import pandas as pd
from win10toast import ToastNotifier
import os

def main():
    seconds = sys.argv[1]
    with open(os.getcwd() + "\productivity.csv", "a") as f:
        f.write(f"{dt.datetime.now()},{seconds}\n")
    show_toast()

def show_toast():
    toaster = ToastNotifier()
    file = pd.read_csv(os.getcwd()+"\productivity.csv", names = ["Date", "Seconds"])
    file = file.set_index("Date")
    file.index = pd.to_datetime(file.index)
    file.loc[dt.datetime.now()] = 0
    seconds_per_day = file.resample('D').Seconds.sum()

    display_dates = 3
    last_3_days = list(zip(seconds_per_day.index[-display_dates:], seconds_per_day.iloc[-display_dates:]))
    last_3_days.reverse()

    message = ""
    for date, seconds in last_3_days:
        message += f"{date.strftime('%a %b %d')}: {str(dt.timedelta(seconds = seconds))}\n"

    toaster.show_toast("Productivity", message, duration = 5, threaded = True, icon_path = os.getcwd()+"\desk.ico")

if __name__ == "__main__":
    main()