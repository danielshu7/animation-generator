## opens the image and sends to Kafka

import io
import time # for sleep
import sys
from kafka import KafkaProducer  # producer of events
from PIL import Image


# acquire the producer
# (you will need to change this to your bootstrap server's IP addr)
producer = KafkaProducer (bootstrap_servers="129.114.25.94:30000", 
                                          acks=1)  # wait for leader to write to log

def read_image():
    with open("images/image.tif", "rb") as image:
        f = image.read()
        b = bytearray(f)
        return b

byte_img = read_image()
time.sleep(5)

# get frame number
file_path = "frame_num.txt"
text_file = open(file_path, "r")
frame = text_file.read()
text_file.close()
frame_num = int(frame)

# send bytes
frame_byte = int(frame_num).to_bytes(1, "little")
byte_img.extend(frame_byte)
producer.send("images", value= byte_img)
producer.flush ()   # try to empty the sending buffer
print("Image sent")


# we are done
producer.close ()
    






