## Receive gif from Kafka and save it

import io
import os   # need this for popen
import time # for sleep
from kafka import KafkaConsumer  # consumer of events
from PIL import Image

start_time = time.time()

# acquire the consumer
# (you will need to change this to your bootstrap server's IP addr)
consumer = KafkaConsumer (bootstrap_servers="129.114.25.94:30001")

# subscribe to topic
consumer.subscribe (topics=["gif"])

# we keep reading and printing
for msg in consumer:

    retrieved_msg = msg.value
    test_image = Image.open(io.BytesIO(retrieved_msg))
    test_image.save("gifs/possibly_corrupt_result.gif", format="GIF", save_all=True)
    break


consumer.close ()
    

print("Total time (cloud compiled):", time.time() - start_time, "seconds")










