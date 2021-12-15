## Sends all scripts from specified folder to Kafka

import glob
import os   # need this for popen
import time # for sleep
import sys
from kafka import KafkaProducer  # producer of events



# acquire the producer
# (you will need to change this to your bootstrap server's IP addr)
producer = KafkaProducer (bootstrap_servers="129.114.25.94:30000",
                                          acks=1)  # wait for leader to write to log

script_dir = sys.argv[1]
scripts_list = sorted(glob.glob("scripts/" + script_dir + "/*"))
for i in range (0,len(scripts_list)):
    # read script file
    file_path = scripts_list[i]
    text_file = open(file_path, "r")
    contents = text_file.read()
    text_file.close()

    byte_contents = bytearray(contents.encode())
    frame_num = i+1
    frame_byte = int(frame_num).to_bytes(1, "little")
    byte_contents.extend(frame_byte)
    producer.send ("script", value=byte_contents)
    producer.flush ()   # try to empty the sending buffer

    # sleep a second
    time.sleep (1)

# we are done
producer.close ()


