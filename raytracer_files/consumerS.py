import time # for sleep
import sys
from kafka import KafkaConsumer  # consumer of events

# We can make this more sophisticated/elegant but for now it is just
# hardcoded to the setup I have on my local VMs

# acquire the consumer
# (you will need to change this to your bootstrap server's IP addr)
consumer = KafkaConsumer (bootstrap_servers="129.114.25.94:30001", group_id="1")

# subscribe to topic
#frame_num = sys.argv[1]
#topic = "script" + frame_num
#consumer.subscribe (topics=[topic])
consumer.subscribe(topics=["script"])

print("Consumer waiting for script")
# we keep reading and printing
for msg in consumer:
    # retrieve script contents and frame number
    retrieved_msg = msg.value
    frame_number = retrieved_msg[-1]
    contents = retrieved_msg[:-1].decode()

    # write the script
    text_file = open("scripts/script.txt", "w")
    text_file.write(contents)
    text_file.close()

    # write the frame_number
    num_file = open("frame_num.txt", "w")
    num_file.write(str(frame_number))
    num_file.close()
    break

# we are done. As such, we are not going to get here as the above loop
# is a forever loop.
consumer.close ()

