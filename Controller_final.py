import serial
import time
import pygame


pygame.init()
j = pygame.joystick.Joystick(0)
j.init()
print ('Initialized Joystick : %s' % j.get_name())

def get():
    out = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    it = 0 #iterator
    pygame.event.pump()
    #Read input from the two joysticks       
    for i in range(0, j.get_numaxes()):
        out[it] = round(j.get_axis(i),1)
        it+=1
    #Read input from buttons
    for i in range(0, j.get_numbuttons()):
        out[it] = j.get_button(i)
        it+=1
    if(abs(out[1])>abs(out[0])):
        out[0]=0.0
    else:
        out[1]=0.0
    if(out[1]==0.1 or out[1]==-0.1):
        out[1]=0.0
    if(out[0]==0.1 or out[0]==-0.1):
        out[0]=0.0
    if(out[3]==0.1 or out[3]==-0.1):
        out[3]=0.0
    if(out[4]==0.1 or out[4]==-0.1):
        out[4]=0.0
    out[1]=out[1]*10
    out[0]=out[0]*10
    out[3]=out[3]*10
    out[4]=out[4]*10
    #s=str(out).strip('[]')
    #data = pickle.dumps(s)
    #return data
    return out


arduino=serial.Serial('COM4', 9600)
time.sleep(2)

print("Enter 1 to turn ON LED and 0 to turn OFF LED")

while 1:
    
    '''datafromUser=input()
    datafromUser=datafromUser+'\r'
    arduino.write(datafromUser.encode())  '''
    x = get()
    for i in range(0,17):
        x[i]=107+int(x[i])
        x[i]=chr(x[i])
            
    ch=''
    for i in range(0,17):
      ch=ch+(x[i])
    ch=ch+'\r'
    print(ch)
    arduino.write(ch.encode())
