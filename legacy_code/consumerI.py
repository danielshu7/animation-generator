## retrieves image from Kafka and saves it

import io
import time # for sleep
from kafka import KafkaConsumer  # consumer of events
from PIL import Image



# acquire the consumer
# (you will need to change this to your bootstrap server's IP addr)
consumer = KafkaConsumer (bootstrap_servers="129.114.25.94:30001", consumer_timeout_ms=30000)

# subscribe to topic
consumer.subscribe (topics=["images"])

# we keep reading and printing
for msg in consumer:
    # what we get is a record. From this record, we are interested in printing
    # the contents of the value field. We are sure that we get only the
    # utilizations topic because that is the only topic we subscribed to.
    # Otherwise we will need to demultiplex the incoming data according to the
    # topic coming in.
    #
    # convert the value field into string (ASCII)
    #
    # Note that I am not showing code to obtain the incoming data as JSON
    # nor am I showing any code to connect to a backend database sink to
    # dump the incoming data. You will have to do that for the assignment.
    retrieved_msg = msg.value
    frame_number = retrieved_msg[-1]
    test_image = Image.open(io.BytesIO(retrieved_msg[:-1]))
    test_image.save("images/image" + str(frame_number) + ".tif")


# we are done. As such, we are not going to get here as the above loop
# is a forever loop.
consumer.close ()
    












