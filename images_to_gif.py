## receives images from Kafka, compiles into gif, and sends back to Kafka

import io
import time # for sleep
from kafka import KafkaConsumer  # consumer of events
from kafka import KafkaProducer
from PIL import Image



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
        if start_time == 0:
            start_time = time.time()
    
        retrieved_msg = msg.value
        frame_number = retrieved_msg[-1]
        image = Image.open(io.BytesIO(retrieved_msg[:-1]))
        unsorted_frames.append((frame_number, image))
        
        
        print(time.time() - start_time)

    consumer.close ()
    

    # sort frames
    unsorted_frames.sort()
    frames = []
    for pair in unsorted_frames:
        frames.append(pair[1])

    # start gif compiling
    if frames:
        print("Compiling into gif")
        producer = KafkaProducer (bootstrap_servers="129.114.25.94:30000", 
                                                  acks=1)  # wait for leader to write to log

        frames[0].save("gifs/result.gif", format="GIF", append_images=frames[1:], save_all=True, duration=100, loop=0)
        
        
        def read_image():
            with open("gifs/result.gif", "rb") as image:
                f = image.read()
                b = bytearray(f)
                return b
        
        
        byte_img = read_image()
        time.sleep(5)
        
        producer.send("gif", value=byte_img)
        producer.flush()  # try to empty the sending buffer
        print("Gif sent")
        
        # we are done
        producer.close()











