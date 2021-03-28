:loop
gen.exe > 1.in && gen_input.exe < 1.in > input.S
main.exe < 1.in > std.out && java -jar venus-jvm-latest.jar heap.S > me.out
fc /N std.out me.out || pause
goto loop