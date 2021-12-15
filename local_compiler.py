#
#
# Author: Aniruddha Gokhale
# CS4287-5287: Principles of Cloud Computing, Vanderbilt University
#
# Created: Sept 6, 2020
#
# Purpose:
#
#    Demonstrate the use of Kafka Python streaming APIs.
#    In this example, demonstrate Kafka streaming API to build a consumer.
#

import io
import time # for sleep
from kafka import KafkaConsumer  # consumer of events
from PIL import Image, ImageSequence

program_start_time = time.time()

# acquire the consumer
# (you will need to change this to your bootstrap server's IP addr)
while True:
    consumer = KafkaConsumer (bootstrap_servers="129.114.25.94:30001", consumer_timeout_ms=20000)

    # subscribe to topic
    consumer.subscribe (topics=["images"])

    # we keep reading and printing
    print("Consumer waiting...")
    start_time = 0
    unsorted_frames = []
    for msg in consumer:
        #if start_time == 0:
        #    start_time = time.time()
    
        retrieved_msg = msg.value
        frame_number = retrieved_msg[-1]
        print(frame_number)
        image = Image.open(io.BytesIO(retrieved_msg[:-1]))
        unsorted_frames.append((frame_number, image))
        
        print(time.time() - program_start_time)

    consumer.close ()
    
    # sort frames
    unsorted_frames.sort()
    frames = []
    for pair in unsorted_frames:
        frames.append(pair[1])

    # start gif part
    if frames:
        print("Total Frames:", len(frames))
        print("Combining to GIF")
        frames[0].save("gifs/final_result.gif", format="GIF", append_images=frames[1:], save_all=True, duration=100, loop=0)
        
        print("GIF saved")
        break

print("Total time (locally compiled):", time.time() - program_start_time, "seconds")








