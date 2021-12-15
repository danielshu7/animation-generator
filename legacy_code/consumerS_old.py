## receives script of specific frame from Kafka

import time # for sleep
import sys
from kafka import KafkaConsumer  # consumer of events

# We can make this more sophisticated/elegant but for now it is just
# hardcoded to the setup I have on my local VMs

# acquire the consumer
# (you will need to change this to your bootstrap server's IP addr)
consumer = KafkaConsumer (bootstrap_servers="129.114.25.94:30001")

# subscribe to topic
frame_num = sys.argv[1]
topic = "script" + frame_num
consumer.subscribe (topics=[topic])

print("Consumer waiting for script")
# we keep reading and printing
for msg in consumer:
    
    retrieved_msg = str(msg.value, 'ascii')
    text_file = open("scripts/script.txt", "w")
    n = text_file.write(retrieved_msg)
    text_file.close()
    break

# we are done. As such, we are not going to get here as the above loop
# is a forever loop.
consumer.close ()
    






