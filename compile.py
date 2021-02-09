import os

print("|----------------------|")
print("|!= ENGINE COMPILE MENU|")
print("|----------------------|")
print(); 
print("|---------|")
print("|Choose OS|")
print("|---------|")
print("|1. WIN   |")
print("|---------|")
print("|2. MAC   |")
print("|---------|")
print("|3. LINUX |")
print("|---------|")
print(); 

os_input = int(input("OS: "))

#os.system("ifconfig")


def compile_win():
    print("Starting compilation of window codebase.")

def compile_mac():
    print("Starting compilation of mac codebase.")

def compile_linux():
    print("Starting compilation of linux codebase.")
    os.system("g++ -c -fPIC thirdparty/linux/glad/glad.c -o linux/build/glad.o")
    os.system("g++ -c -fPIC core/log/log.cpp -o linux/build/log.o")
    os.system("g++ -c -fPIC core/graphics/texture.cpp -o linux/build/texture.o")
if os_input == 1:
    compile_win()
elif os_input == 2:
    compile_mac()
elif os_input == 3:
    compile_linux()

