	
	while(1) {
		switch(ch = getchar()) {
			case '7': mt.lf(); break;
			case '9': mt.rf(); break;
			case '1': mt.lb(); break;
			case '3': mt.rb(); break;
			case '5': mt.stop(); break;
			case 'w': servo.pulse(p += 10); break;
			case 's': servo.pulse(p -= 10); break;
			case 'a': step.clock(a = -10); break;
			case 'd': step.clock(a = 10); break;
			case '4': mt.left(); break;
			case '6': mt.right(); break;
			case '8': mt.fw(); break;
			case '2': mt.bw(); break;
			case 'q': return 0;
			default: ; 
		}}

