# Cloud-Based Ray Tracing Animation Generator

## Introduction
Ray tracing is a graphics rendering technique that is powerful but has historically been extremely time and computationally expensive. Until very recent times, other techniques have been more popular for applications that require quick responses (such as real-time graphics). Cloud technologies have the capability to provide us the resources to overcome some of the speed limitations of traditional ray tracing. We have developed an application that utilizes this combination of technologies to quickly and accurately generate animated images.

## Directories
*ansible_files*: contains all ansible playbooks used for setting up OpenStack VMs and running Kubernetes workload resources  
*gifs*: contains sample GIF outputs.  New outputs will also be saved here as "final_result.gif" (locally compiled) and "possibly_corrupt_result.gif" (cloud compiled)  
*images*: contains some intermediate image frames rendered or used during the testing phase  
*kubernetes_files*: contains all YAML files for Kubernetes workload resources and services  
*legacy_code*: contains some Python programs that were initially used in the pipeline  
*raytracer_files*: contains all necessary files for the ray tracer pods; also contains some additional graphics functionalities beyond ray tracing that are unused in this project  
*scripts*: contains all our sample input scripts in addition to some helper Python programs

## Python Files
*animation_generator.py*: the main program. Runs producerS.py, local_compiler.py, and consumerG.py concurrently.  
*producerS.py*: sends scripts to the Kafka service in the cloud.  Located on local device.  
*consumerS.py*: receives scripts from Kafka service and saves them.  Located in each ray tracer pod.
*producerI.py*: sends image to the Kafka service.  Located in each ray tracer pod.  
*local_compiler.py*: receives image frames from the Kafka service.  After 20 seconds has elapsed with no new frames, compiles the frames into a gif and saves it.  Located on local device.  
*images_to_gif.py*: receives image frames from the Kafka service.  After 20 seconds has elapsed with no new frames, compiles the frames into a gif and sends it to the Kafka service.  Located in cloud GIF compiler.  
*consumerG.py*: receives gif from the Kafka service and saves it.  Located on local device.

## Demo Video
https://studio.youtube.com/channel/UC0lp19qtOG8nbm_UIUK-o1w/videos/upload?filter=%5B%5D&sort=%7B%22columnType%22%3A%22date%22%2C%22sortOrder%22%3A%22DESCENDING%22%7D
