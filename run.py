import os

a = input("Please select the project you wish to run by typing the corresponding number.\n 1.Sandbox\n 2.Boids\n")
a = int(a)

os.chdir("Jellyfish3D")
# os.system("../bin/linux-x86_64-Debug/Jellyfish3D/Jellyfish3D")

if a == 1:
    os.system("../bin/linux-x86_64-Debug/Sandbox/Sandbox")
if a == 2:
    os.system("../bin/linux-x86_64-Debug/Boids/Boids")
