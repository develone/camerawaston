import picamera                  # import files

camera = picamera.PiCamera()     # initialize camera
camera.color_effects = (128,128) # turn camera to black and white
camera.resolution = (256, 256)
camera.hflip = True
camera.vflip = True
camera.capture('image1.bmp')     # take a shot
