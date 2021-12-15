import io
import time # for sleep
from kafka import KafkaConsumer  # consumer of events
from kafka import KafkaProducer
from PIL import Image

# We can make this more sophisticated/elegant but for now it is just
# hardcoded to the setup I have on my local VMs

# acquire the consumer
# (you will need to change this to your bootstrap server's IP addr)
while True:
    consumer = KafkaConsumer (bootstrap_servers="129.114.25.94:30001", consumer_timeout_ms=20000)

    # subscribe to topic
    consumer.subscribe (topics=["images"])

    # we keep reading and printing
    print("Consumer waiting...")
    start_time = 0
    frames = []
    for msg in consumer:
        if start_time == 0:
            start_time = time.time()
    
        retrieved_msg = msg.value
        frame_number = retrieved_msg[-1]
        frames.append(Image.open(io.BytesIO(retrieved_msg[:-1])))
        
        print(time.time() - start_time)

    consumer.close ()
    


    # start gif part
    if frames:
        print("Combining to gif")
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


