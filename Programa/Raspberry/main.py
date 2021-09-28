# Libraries

import serial  # serial port

from flask import Flask, render_template, request  # flask utils
import flask
import json


class log:
    def __init__(self, max=600):
        self.items = []
        self.max = max

    def add(self, msg, rx=False):
        self.items.append([rx, msg])
        print(type(len(self.items)))

    def pop(self, x=0):
        self.items.pop(x)

    def get_log(self):
        return self.items


app = Flask(__name__)  # flask init

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600)

data_log = log(500)


@app.route("/")  # Home page
def root():
    test_array = data_log.get_log()

    return render_template("test1.html", input_from_python=test_array)


@app.route("/get", methods=["POST"])  # Get the messange to send
def test_get():
    form = request.form
    print(form)
    msg = request.form["msg"]
    print("*********************")
    print(f"The mensage to send is: {msg}")
    print("*********************\n")
    if msg != "":
        data_log.add(msg)
        send = msg + "\r\n"
        print(data_log.get_log())
        ser.write(send.encode())
        return msg
    return "Empty"


def event_serial(ser):
    str = ser.readline().decode()
    yield 'data:' + ''.join(str) + '\n\n'


@app.route('/barcode')
def serial_update():
    newresponse = flask.Response(event_serial(ser),
                                 mimetype="text/event-stream")
    newresponse.headers.add('Access-Control-Allow-Origin', '*')
    newresponse.headers.add('Cache-Control', 'no-cache')
    print(f"type -> {newresponse.data}")
    msg_ = newresponse.data.decode().rstrip().replace("data:", "")
    data_log.add(msg_, rx=True)
    print("---------------------")
    print(f"| Mensage recibed: {msg_} ")
    print("---------------------\n")
    print(data_log.get_log())
    return newresponse


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True, threaded=True)
