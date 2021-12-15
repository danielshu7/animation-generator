## sends script to Kafka

import os   # need this for popen
import time # for sleep
from kafka import KafkaProducer  # producer of events


# acquire the producer
# (you will need to change this to your bootstrap server's IP addr)
producer = KafkaProducer (bootstrap_servers="129.114.25.94:30000",
                                          acks=1)  # wait for leader to write to log

# say we send the contents 100 times after a sleep of 1 sec in between
for i in range (1):
    # read script file
    file_path = "scripts/basic.txt"
    text_file = open(file_path, "r")
    contents = text_file.read()
    text_file.close()

    producer.send ("scripts", value=bytes(contents, 'ascii'))
    producer.flush ()   # try to empty the sending buffer

    # sleep a second
    time.sleep (1)

# we are done
producer.close ()
