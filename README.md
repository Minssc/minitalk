# minitalk

[Mandatory]
You must create a communicaion proram in the form of a client and server.

The server must be launched first, and after being launched it must display its PID.

The client will take as parameters:
  -The server PID.
  -The string that should be sent.
  
The client must communicate the string passed as a parameter to the server. Once the string has been received, the sever must display it.
  
Communication between your programs should ONLY be done using UNIX signals.
  
The server must be able to display the string pretty quickly. By quickly we mean that if you think it is too long, then it is probably too long (hint: 1 second for 100 characters is COLOSSAL)
  
Your server should be able to receive strings from several clients in a row, without needing to be restarted.
  
You can only use the two signals SIGUSR1 and SIGUSR2
  
[Bonus]
Add a small reception acknowledgement system.

support Unicode characters!

tl;dr
  Make a client-server pair that sends and receives string using only UNIX signals (SIGUSR1, SIGUSR2)

SIGUSR1 SIGUSR2 두개 signal을 각각 0, 1비트로 처리 

처리되지 못한 signal은 씹히기 때문에 무작정 상수값 usleep후 kill() 호출하는 방식으론 한계가 있음.
  kill() 사이 usleep 시간을 늘리면 전체 전송시간이 늘어남. 서브젝트에서 주관적으로 느림을 판단하라는데... 평가자 맘이네? 
  kill() 사이 usleep 시간을 줄이면 서버단에서 signal이 뭉개져서 데이터가 깨질 수 있음. 
  
시그널은 kill()을 호출하면 송신은 보장되나 수신은 보장되지 않음. (수신자가 바빠서 signal 처리를 못하는 경우 등)

따라서 네트워크 통신에서 하듯 클라이언트가 보낸 signal(bit)에 대한 awk를 서버가 답해야 다음 비트를 보내는 방식을 사용함. awk를 받지 못하면 재전송
  signal 핑퐁이 매우 빠르게 진행되기 때문에 상수 usleep보다 월등히 빠른 속도로 정확한 데이터를 주고받는다. 
  모든 signal(bit)에 대해 awk를 확인하기 때문에 정상 종료시 메시지를 제대로 보냈다는걸 확정적으로 알 수 있다. 
    보너스의 acknowledgement system이 바로 clear!
  문자열을 비트단위로 바이트 전체를 보내기 대문에 유니코드도 아무 문제 없음.
    보너스의 support unicode characters 바로 clear!

길이 100(+1)의 문자열을 송신하는데 걸리는 시간(time)
  real    0m0.037s
  user    0m0.030s  
  sys     0m0.000s

서브젝트 힌트는 100개 문자 1초면 심각하다고 보니... 0.037초면 ok
