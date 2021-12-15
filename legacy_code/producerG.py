## reads images and compiles into a gif; then sends it to Kafka

import glob
import io
import time # for sleep
from kafka import KafkaProducer  # producer of events
from PIL import Image



# acquire the producer
# (you will need to change this to your bootstrap server's IP addr)
producer = KafkaProducer (bootstrap_servers="129.114.25.94:30000", 
                                          acks=1)  # wait for leader to write to log


frames = []
imgs = sorted(glob.glob("images/*"))

for i in imgs:
    print(i)
    new_frame = Image.open(i)
    frames.append(new_frame)
    
frames[0].save("gifs/result.gif", format="GIF", append_images=frames[1:], save_all=True, duration=1000, loop=0)


def read_image():
    with open("gifs/result.gif", "rb") as image:
        f = image.read()
        b = bytearray(f)
        return b


byte_img = read_image()
time.sleep(10)


producer.send ("gif", value= byte_img)
producer.flush ()   # try to empty the sending buffer
print("Gif sent")



# we are done
producer.close ()

    






