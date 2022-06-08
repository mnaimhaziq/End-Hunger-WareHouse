import requests
import json
import time
import serial
import serial.tools.list_ports as listport

url = "https://apiv2.favoriot.com/v2/streams"

ports = listport.comports()
serialInst = serial.Serial()


def streamData(device_developer_id, accesstoken, item, water_level):

    params = {
        'device_developer_id': device_developer_id,
        'data': {
            'item': item,
            'waterlevel': water_level
        }
    }
    headers = {
        'accesstoken': accesstoken,
        'content-type': "application/json",
        'cache-control': "no-cache",
    }

    respons = requests.post(url, data=json.dumps(params), headers=headers)
    print(respons.text)


if __name__ == '__main__':
    ser = serial.Serial('COM6', 9600, timeout=0)
    ser.reset_input_buffer()
    # device_developer_id = 'deviceDefault@naimbuse'
    # accesstoken = 'op64KzIs5sGP07V5aTl1u7lV1YW1ixoa'
    device_developer_id = 'deviceDefault@hehehe'
    accesstoken = 'g8sV6zYhMXnCVlNmafyEGYGoZk6I7siN'
    while True:
        line = ser.readall()
        if line:
            # convert the byte string to a unicode string
            line = line.decode('utf-8').rstrip()
            inputData = line.split(' ')
            if len(inputData) == 2 and inputData[0] != '':
                tempItem = bool(float(inputData[0]))
                if tempItem:
                    item = 1
                else:
                    item = 0
                water_level = float(inputData[1])
                streamData(device_developer_id, accesstoken, item, water_level)
