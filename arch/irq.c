#include <keyboard.h>
#include <drivers/RTL8139.h>
#include <kprint.h>
#include <desc.h>
#include <pic.h>
#include <irq.h>
#include <cpu.h>
#include <io.h>
#include <scheduler.h>
#include <syscalls.h>
#include <panic.h>

/*
 * This file handles setting up the interrupts.
 */

void initalize_idt();

extern void generic_interrupt_wrapper();

void exception_handler(int vector){
	kprintf("<!>\n");
	switch(vector){
		case 0:
			kprintf("fault: divide error\n");
			break;
		case 1:
			kprintf("fault/trap: debug exception\n");
			break;
		case 2:
			kprintf("Nonmaskable Interrupt\n");
			break;
		case 3:
			kprintf("breakpoint\n");
			break;
		case 4:
			kprintf("overflow\n");
			break;
		case 5:
			kprintf("BOUND range exceeded\n");
			break;
		case 6:
			kprintf("Invalid opcode\n");
			break;
		case 7:
			kprintf("device not available\n");
			break;
		case 8:
			kprintf("Double fault\n");
			break;
		case 9:
			kprintf("Coprocessor Segment Overrun\n");
			break;
		case 10:
			kprintf("invalid TSS\n");
			break;
		case 11:
			kprintf("Segment Not Present\n");
			break;
		case 12:
			kprintf("stack-segment fault\n");
			break;
		case 13:
			kprintf("General Protection\n");
			break;
		case 14:
			kprintf("page fault\n");
			break;
		case 15:
			kprintf("Intel Reserved\n");
			break;
		case 16:
			kprintf("x87 FPU floating-point error\n");
			break;
		case 17:
			kprintf("alignment check\n");
			break;
		case 18:
			kprintf("machine check\n");
			break;
		case 19:
			kprintf("SIMD Floating-Point Exception\n");
			break;
		case 20:
			kprintf("Virtualization Exception\n");
			break;
	}
}

void generic_interrupt_handler(struct cpu_state s)
{
	int sched=0;/*wether or not to schedule after this interrupt*/
	if(s.vector<20){
		exception_handler(s.vector);
		goto non_handled;
	}

	if(s.vector==0x20)/*then its just a timer, we don't have to care*/
		goto ret;

	if(s.vector==0x21){
		keyboard_irq();
		goto ret;
	}

	if(s.vector==0x2b){
		rtl_handle_interrupt();
		goto ret;
	}

	if(s.vector==0x80){
		/*we know a process called us, so we save our state*/
		sched_procs[current_process].regs=s;
		sched_procs[current_process].regs.esp+=16;
		sched=1;
		system_call(&s);
		goto ret;
	}

non_handled:
	kprintf("s.vector:%x\n",s.vector);
	panic("non-handled interrupt");
ret:
	acknowledge_interrupt(s.vector);
	if(sched){
		s=sched_procs[current_process].regs;/*we mighta changed em*/
		sched_tick();
	}
}

void initalize_idt_entry(int vector, void (*func)(void))
{
	unsigned long addr = (unsigned long)func;
	int high_address = addr & 0xFFFF0000;
	int low_address  = addr & 0x0000FFFF;
	int DPL = 0;/*descriptor privilege level*/
	int P = 1;/*selector present flag*/
	int Selector = 1<<3;/*segment selector for destination code segment.*/
	int D = 1;/*size of gate: 1=32bit; 0=16bit*/
	int type=14;
	idt_table[vector].b=high_address;
	idt_table[vector].b|=P<<15;
	idt_table[vector].b|=DPL<<13;
	idt_table[vector].b|=D<<11;
	idt_table[vector].b|=type<<8;

	idt_table[vector].a=low_address;
	idt_table[vector].a|=Selector<<16;
}

void initalize_interrupts()
{
	initalize_idt();
	idt_descr.size=(256*8)-1;
	idt_descr.address=(unsigned int)idt_table;
	load_idt(&idt_descr);
}

/* see you on the far side... */
extern void interrupt_wrapper_0();
extern void interrupt_wrapper_1();
extern void interrupt_wrapper_2();
extern void interrupt_wrapper_3();
extern void interrupt_wrapper_4();
extern void interrupt_wrapper_5();
extern void interrupt_wrapper_6();
extern void interrupt_wrapper_7();
extern void interrupt_wrapper_8();
extern void interrupt_wrapper_9();
extern void interrupt_wrapper_10();
extern void interrupt_wrapper_11();
extern void interrupt_wrapper_12();
extern void interrupt_wrapper_13();
extern void interrupt_wrapper_14();
extern void interrupt_wrapper_15();
extern void interrupt_wrapper_16();
extern void interrupt_wrapper_17();
extern void interrupt_wrapper_18();
extern void interrupt_wrapper_19();
extern void interrupt_wrapper_20();
extern void interrupt_wrapper_21();
extern void interrupt_wrapper_22();
extern void interrupt_wrapper_23();
extern void interrupt_wrapper_24();
extern void interrupt_wrapper_25();
extern void interrupt_wrapper_26();
extern void interrupt_wrapper_27();
extern void interrupt_wrapper_28();
extern void interrupt_wrapper_29();
extern void interrupt_wrapper_30();
extern void interrupt_wrapper_31();
extern void interrupt_wrapper_32();
extern void interrupt_wrapper_33();
extern void interrupt_wrapper_34();
extern void interrupt_wrapper_35();
extern void interrupt_wrapper_36();
extern void interrupt_wrapper_37();
extern void interrupt_wrapper_38();
extern void interrupt_wrapper_39();
extern void interrupt_wrapper_40();
extern void interrupt_wrapper_41();
extern void interrupt_wrapper_42();
extern void interrupt_wrapper_43();
extern void interrupt_wrapper_44();
extern void interrupt_wrapper_45();
extern void interrupt_wrapper_46();
extern void interrupt_wrapper_47();
extern void interrupt_wrapper_48();
extern void interrupt_wrapper_49();
extern void interrupt_wrapper_50();
extern void interrupt_wrapper_51();
extern void interrupt_wrapper_52();
extern void interrupt_wrapper_53();
extern void interrupt_wrapper_54();
extern void interrupt_wrapper_55();
extern void interrupt_wrapper_56();
extern void interrupt_wrapper_57();
extern void interrupt_wrapper_58();
extern void interrupt_wrapper_59();
extern void interrupt_wrapper_60();
extern void interrupt_wrapper_61();
extern void interrupt_wrapper_62();
extern void interrupt_wrapper_63();
extern void interrupt_wrapper_64();
extern void interrupt_wrapper_65();
extern void interrupt_wrapper_66();
extern void interrupt_wrapper_67();
extern void interrupt_wrapper_68();
extern void interrupt_wrapper_69();
extern void interrupt_wrapper_70();
extern void interrupt_wrapper_71();
extern void interrupt_wrapper_72();
extern void interrupt_wrapper_73();
extern void interrupt_wrapper_74();
extern void interrupt_wrapper_75();
extern void interrupt_wrapper_76();
extern void interrupt_wrapper_77();
extern void interrupt_wrapper_78();
extern void interrupt_wrapper_79();
extern void interrupt_wrapper_80();
extern void interrupt_wrapper_81();
extern void interrupt_wrapper_82();
extern void interrupt_wrapper_83();
extern void interrupt_wrapper_84();
extern void interrupt_wrapper_85();
extern void interrupt_wrapper_86();
extern void interrupt_wrapper_87();
extern void interrupt_wrapper_88();
extern void interrupt_wrapper_89();
extern void interrupt_wrapper_90();
extern void interrupt_wrapper_91();
extern void interrupt_wrapper_92();
extern void interrupt_wrapper_93();
extern void interrupt_wrapper_94();
extern void interrupt_wrapper_95();
extern void interrupt_wrapper_96();
extern void interrupt_wrapper_97();
extern void interrupt_wrapper_98();
extern void interrupt_wrapper_99();
extern void interrupt_wrapper_100();
extern void interrupt_wrapper_101();
extern void interrupt_wrapper_102();
extern void interrupt_wrapper_103();
extern void interrupt_wrapper_104();
extern void interrupt_wrapper_105();
extern void interrupt_wrapper_106();
extern void interrupt_wrapper_107();
extern void interrupt_wrapper_108();
extern void interrupt_wrapper_109();
extern void interrupt_wrapper_110();
extern void interrupt_wrapper_111();
extern void interrupt_wrapper_112();
extern void interrupt_wrapper_113();
extern void interrupt_wrapper_114();
extern void interrupt_wrapper_115();
extern void interrupt_wrapper_116();
extern void interrupt_wrapper_117();
extern void interrupt_wrapper_118();
extern void interrupt_wrapper_119();
extern void interrupt_wrapper_120();
extern void interrupt_wrapper_121();
extern void interrupt_wrapper_122();
extern void interrupt_wrapper_123();
extern void interrupt_wrapper_124();
extern void interrupt_wrapper_125();
extern void interrupt_wrapper_126();
extern void interrupt_wrapper_127();
extern void interrupt_wrapper_128();
extern void interrupt_wrapper_129();
extern void interrupt_wrapper_130();
extern void interrupt_wrapper_131();
extern void interrupt_wrapper_132();
extern void interrupt_wrapper_133();
extern void interrupt_wrapper_134();
extern void interrupt_wrapper_135();
extern void interrupt_wrapper_136();
extern void interrupt_wrapper_137();
extern void interrupt_wrapper_138();
extern void interrupt_wrapper_139();
extern void interrupt_wrapper_140();
extern void interrupt_wrapper_141();
extern void interrupt_wrapper_142();
extern void interrupt_wrapper_143();
extern void interrupt_wrapper_144();
extern void interrupt_wrapper_145();
extern void interrupt_wrapper_146();
extern void interrupt_wrapper_147();
extern void interrupt_wrapper_148();
extern void interrupt_wrapper_149();
extern void interrupt_wrapper_150();
extern void interrupt_wrapper_151();
extern void interrupt_wrapper_152();
extern void interrupt_wrapper_153();
extern void interrupt_wrapper_154();
extern void interrupt_wrapper_155();
extern void interrupt_wrapper_156();
extern void interrupt_wrapper_157();
extern void interrupt_wrapper_158();
extern void interrupt_wrapper_159();
extern void interrupt_wrapper_160();
extern void interrupt_wrapper_161();
extern void interrupt_wrapper_162();
extern void interrupt_wrapper_163();
extern void interrupt_wrapper_164();
extern void interrupt_wrapper_165();
extern void interrupt_wrapper_166();
extern void interrupt_wrapper_167();
extern void interrupt_wrapper_168();
extern void interrupt_wrapper_169();
extern void interrupt_wrapper_170();
extern void interrupt_wrapper_171();
extern void interrupt_wrapper_172();
extern void interrupt_wrapper_173();
extern void interrupt_wrapper_174();
extern void interrupt_wrapper_175();
extern void interrupt_wrapper_176();
extern void interrupt_wrapper_177();
extern void interrupt_wrapper_178();
extern void interrupt_wrapper_179();
extern void interrupt_wrapper_180();
extern void interrupt_wrapper_181();
extern void interrupt_wrapper_182();
extern void interrupt_wrapper_183();
extern void interrupt_wrapper_184();
extern void interrupt_wrapper_185();
extern void interrupt_wrapper_186();
extern void interrupt_wrapper_187();
extern void interrupt_wrapper_188();
extern void interrupt_wrapper_189();
extern void interrupt_wrapper_190();
extern void interrupt_wrapper_191();
extern void interrupt_wrapper_192();
extern void interrupt_wrapper_193();
extern void interrupt_wrapper_194();
extern void interrupt_wrapper_195();
extern void interrupt_wrapper_196();
extern void interrupt_wrapper_197();
extern void interrupt_wrapper_198();
extern void interrupt_wrapper_199();
extern void interrupt_wrapper_200();
extern void interrupt_wrapper_201();
extern void interrupt_wrapper_202();
extern void interrupt_wrapper_203();
extern void interrupt_wrapper_204();
extern void interrupt_wrapper_205();
extern void interrupt_wrapper_206();
extern void interrupt_wrapper_207();
extern void interrupt_wrapper_208();
extern void interrupt_wrapper_209();
extern void interrupt_wrapper_210();
extern void interrupt_wrapper_211();
extern void interrupt_wrapper_212();
extern void interrupt_wrapper_213();
extern void interrupt_wrapper_214();
extern void interrupt_wrapper_215();
extern void interrupt_wrapper_216();
extern void interrupt_wrapper_217();
extern void interrupt_wrapper_218();
extern void interrupt_wrapper_219();
extern void interrupt_wrapper_220();
extern void interrupt_wrapper_221();
extern void interrupt_wrapper_222();
extern void interrupt_wrapper_223();
extern void interrupt_wrapper_224();
extern void interrupt_wrapper_225();
extern void interrupt_wrapper_226();
extern void interrupt_wrapper_227();
extern void interrupt_wrapper_228();
extern void interrupt_wrapper_229();
extern void interrupt_wrapper_230();
extern void interrupt_wrapper_231();
extern void interrupt_wrapper_232();
extern void interrupt_wrapper_233();
extern void interrupt_wrapper_234();
extern void interrupt_wrapper_235();
extern void interrupt_wrapper_236();
extern void interrupt_wrapper_237();
extern void interrupt_wrapper_238();
extern void interrupt_wrapper_239();
extern void interrupt_wrapper_240();
extern void interrupt_wrapper_241();
extern void interrupt_wrapper_242();
extern void interrupt_wrapper_243();
extern void interrupt_wrapper_244();
extern void interrupt_wrapper_245();
extern void interrupt_wrapper_246();
extern void interrupt_wrapper_247();
extern void interrupt_wrapper_248();
extern void interrupt_wrapper_249();
extern void interrupt_wrapper_250();
extern void interrupt_wrapper_251();
extern void interrupt_wrapper_252();
extern void interrupt_wrapper_253();
extern void interrupt_wrapper_254();
extern void interrupt_wrapper_255();

void initalize_idt(){
	initalize_idt_entry(0,interrupt_wrapper_0);
	initalize_idt_entry(1,interrupt_wrapper_1);
	initalize_idt_entry(2,interrupt_wrapper_2);
	initalize_idt_entry(3,interrupt_wrapper_3);
	initalize_idt_entry(4,interrupt_wrapper_4);
	initalize_idt_entry(5,interrupt_wrapper_5);
	initalize_idt_entry(6,interrupt_wrapper_6);
	initalize_idt_entry(7,interrupt_wrapper_7);
	initalize_idt_entry(8,interrupt_wrapper_8);
	initalize_idt_entry(9,interrupt_wrapper_9);
	initalize_idt_entry(10,interrupt_wrapper_10);
	initalize_idt_entry(11,interrupt_wrapper_11);
	initalize_idt_entry(12,interrupt_wrapper_12);
	initalize_idt_entry(13,interrupt_wrapper_13);
	initalize_idt_entry(14,interrupt_wrapper_14);
	initalize_idt_entry(15,interrupt_wrapper_15);
	initalize_idt_entry(16,interrupt_wrapper_16);
	initalize_idt_entry(17,interrupt_wrapper_17);
	initalize_idt_entry(18,interrupt_wrapper_18);
	initalize_idt_entry(19,interrupt_wrapper_19);
	initalize_idt_entry(20,interrupt_wrapper_20);
	initalize_idt_entry(21,interrupt_wrapper_21);
	initalize_idt_entry(22,interrupt_wrapper_22);
	initalize_idt_entry(23,interrupt_wrapper_23);
	initalize_idt_entry(24,interrupt_wrapper_24);
	initalize_idt_entry(25,interrupt_wrapper_25);
	initalize_idt_entry(26,interrupt_wrapper_26);
	initalize_idt_entry(27,interrupt_wrapper_27);
	initalize_idt_entry(28,interrupt_wrapper_28);
	initalize_idt_entry(29,interrupt_wrapper_29);
	initalize_idt_entry(30,interrupt_wrapper_30);
	initalize_idt_entry(31,interrupt_wrapper_31);
	initalize_idt_entry(32,interrupt_wrapper_32);
	initalize_idt_entry(33,interrupt_wrapper_33);
	initalize_idt_entry(34,interrupt_wrapper_34);
	initalize_idt_entry(35,interrupt_wrapper_35);
	initalize_idt_entry(36,interrupt_wrapper_36);
	initalize_idt_entry(37,interrupt_wrapper_37);
	initalize_idt_entry(38,interrupt_wrapper_38);
	initalize_idt_entry(39,interrupt_wrapper_39);
	initalize_idt_entry(40,interrupt_wrapper_40);
	initalize_idt_entry(41,interrupt_wrapper_41);
	initalize_idt_entry(42,interrupt_wrapper_42);
	initalize_idt_entry(43,interrupt_wrapper_43);
	initalize_idt_entry(44,interrupt_wrapper_44);
	initalize_idt_entry(45,interrupt_wrapper_45);
	initalize_idt_entry(46,interrupt_wrapper_46);
	initalize_idt_entry(47,interrupt_wrapper_47);
	initalize_idt_entry(48,interrupt_wrapper_48);
	initalize_idt_entry(49,interrupt_wrapper_49);
	initalize_idt_entry(50,interrupt_wrapper_50);
	initalize_idt_entry(51,interrupt_wrapper_51);
	initalize_idt_entry(52,interrupt_wrapper_52);
	initalize_idt_entry(53,interrupt_wrapper_53);
	initalize_idt_entry(54,interrupt_wrapper_54);
	initalize_idt_entry(55,interrupt_wrapper_55);
	initalize_idt_entry(56,interrupt_wrapper_56);
	initalize_idt_entry(57,interrupt_wrapper_57);
	initalize_idt_entry(58,interrupt_wrapper_58);
	initalize_idt_entry(59,interrupt_wrapper_59);
	initalize_idt_entry(60,interrupt_wrapper_60);
	initalize_idt_entry(61,interrupt_wrapper_61);
	initalize_idt_entry(62,interrupt_wrapper_62);
	initalize_idt_entry(63,interrupt_wrapper_63);
	initalize_idt_entry(64,interrupt_wrapper_64);
	initalize_idt_entry(65,interrupt_wrapper_65);
	initalize_idt_entry(66,interrupt_wrapper_66);
	initalize_idt_entry(67,interrupt_wrapper_67);
	initalize_idt_entry(68,interrupt_wrapper_68);
	initalize_idt_entry(69,interrupt_wrapper_69);
	initalize_idt_entry(70,interrupt_wrapper_70);
	initalize_idt_entry(71,interrupt_wrapper_71);
	initalize_idt_entry(72,interrupt_wrapper_72);
	initalize_idt_entry(73,interrupt_wrapper_73);
	initalize_idt_entry(74,interrupt_wrapper_74);
	initalize_idt_entry(75,interrupt_wrapper_75);
	initalize_idt_entry(76,interrupt_wrapper_76);
	initalize_idt_entry(77,interrupt_wrapper_77);
	initalize_idt_entry(78,interrupt_wrapper_78);
	initalize_idt_entry(79,interrupt_wrapper_79);
	initalize_idt_entry(80,interrupt_wrapper_80);
	initalize_idt_entry(81,interrupt_wrapper_81);
	initalize_idt_entry(82,interrupt_wrapper_82);
	initalize_idt_entry(83,interrupt_wrapper_83);
	initalize_idt_entry(84,interrupt_wrapper_84);
	initalize_idt_entry(85,interrupt_wrapper_85);
	initalize_idt_entry(86,interrupt_wrapper_86);
	initalize_idt_entry(87,interrupt_wrapper_87);
	initalize_idt_entry(88,interrupt_wrapper_88);
	initalize_idt_entry(89,interrupt_wrapper_89);
	initalize_idt_entry(90,interrupt_wrapper_90);
	initalize_idt_entry(91,interrupt_wrapper_91);
	initalize_idt_entry(92,interrupt_wrapper_92);
	initalize_idt_entry(93,interrupt_wrapper_93);
	initalize_idt_entry(94,interrupt_wrapper_94);
	initalize_idt_entry(95,interrupt_wrapper_95);
	initalize_idt_entry(96,interrupt_wrapper_96);
	initalize_idt_entry(97,interrupt_wrapper_97);
	initalize_idt_entry(98,interrupt_wrapper_98);
	initalize_idt_entry(99,interrupt_wrapper_99);
	initalize_idt_entry(100,interrupt_wrapper_100);
	initalize_idt_entry(101,interrupt_wrapper_101);
	initalize_idt_entry(102,interrupt_wrapper_102);
	initalize_idt_entry(103,interrupt_wrapper_103);
	initalize_idt_entry(104,interrupt_wrapper_104);
	initalize_idt_entry(105,interrupt_wrapper_105);
	initalize_idt_entry(106,interrupt_wrapper_106);
	initalize_idt_entry(107,interrupt_wrapper_107);
	initalize_idt_entry(108,interrupt_wrapper_108);
	initalize_idt_entry(109,interrupt_wrapper_109);
	initalize_idt_entry(110,interrupt_wrapper_110);
	initalize_idt_entry(111,interrupt_wrapper_111);
	initalize_idt_entry(112,interrupt_wrapper_112);
	initalize_idt_entry(113,interrupt_wrapper_113);
	initalize_idt_entry(114,interrupt_wrapper_114);
	initalize_idt_entry(115,interrupt_wrapper_115);
	initalize_idt_entry(116,interrupt_wrapper_116);
	initalize_idt_entry(117,interrupt_wrapper_117);
	initalize_idt_entry(118,interrupt_wrapper_118);
	initalize_idt_entry(119,interrupt_wrapper_119);
	initalize_idt_entry(120,interrupt_wrapper_120);
	initalize_idt_entry(121,interrupt_wrapper_121);
	initalize_idt_entry(122,interrupt_wrapper_122);
	initalize_idt_entry(123,interrupt_wrapper_123);
	initalize_idt_entry(124,interrupt_wrapper_124);
	initalize_idt_entry(125,interrupt_wrapper_125);
	initalize_idt_entry(126,interrupt_wrapper_126);
	initalize_idt_entry(127,interrupt_wrapper_127);
	initalize_idt_entry(128,interrupt_wrapper_128);
	initalize_idt_entry(129,interrupt_wrapper_129);
	initalize_idt_entry(130,interrupt_wrapper_130);
	initalize_idt_entry(131,interrupt_wrapper_131);
	initalize_idt_entry(132,interrupt_wrapper_132);
	initalize_idt_entry(133,interrupt_wrapper_133);
	initalize_idt_entry(134,interrupt_wrapper_134);
	initalize_idt_entry(135,interrupt_wrapper_135);
	initalize_idt_entry(136,interrupt_wrapper_136);
	initalize_idt_entry(137,interrupt_wrapper_137);
	initalize_idt_entry(138,interrupt_wrapper_138);
	initalize_idt_entry(139,interrupt_wrapper_139);
	initalize_idt_entry(140,interrupt_wrapper_140);
	initalize_idt_entry(141,interrupt_wrapper_141);
	initalize_idt_entry(142,interrupt_wrapper_142);
	initalize_idt_entry(143,interrupt_wrapper_143);
	initalize_idt_entry(144,interrupt_wrapper_144);
	initalize_idt_entry(145,interrupt_wrapper_145);
	initalize_idt_entry(146,interrupt_wrapper_146);
	initalize_idt_entry(147,interrupt_wrapper_147);
	initalize_idt_entry(148,interrupt_wrapper_148);
	initalize_idt_entry(149,interrupt_wrapper_149);
	initalize_idt_entry(150,interrupt_wrapper_150);
	initalize_idt_entry(151,interrupt_wrapper_151);
	initalize_idt_entry(152,interrupt_wrapper_152);
	initalize_idt_entry(153,interrupt_wrapper_153);
	initalize_idt_entry(154,interrupt_wrapper_154);
	initalize_idt_entry(155,interrupt_wrapper_155);
	initalize_idt_entry(156,interrupt_wrapper_156);
	initalize_idt_entry(157,interrupt_wrapper_157);
	initalize_idt_entry(158,interrupt_wrapper_158);
	initalize_idt_entry(159,interrupt_wrapper_159);
	initalize_idt_entry(160,interrupt_wrapper_160);
	initalize_idt_entry(161,interrupt_wrapper_161);
	initalize_idt_entry(162,interrupt_wrapper_162);
	initalize_idt_entry(163,interrupt_wrapper_163);
	initalize_idt_entry(164,interrupt_wrapper_164);
	initalize_idt_entry(165,interrupt_wrapper_165);
	initalize_idt_entry(166,interrupt_wrapper_166);
	initalize_idt_entry(167,interrupt_wrapper_167);
	initalize_idt_entry(168,interrupt_wrapper_168);
	initalize_idt_entry(169,interrupt_wrapper_169);
	initalize_idt_entry(170,interrupt_wrapper_170);
	initalize_idt_entry(171,interrupt_wrapper_171);
	initalize_idt_entry(172,interrupt_wrapper_172);
	initalize_idt_entry(173,interrupt_wrapper_173);
	initalize_idt_entry(174,interrupt_wrapper_174);
	initalize_idt_entry(175,interrupt_wrapper_175);
	initalize_idt_entry(176,interrupt_wrapper_176);
	initalize_idt_entry(177,interrupt_wrapper_177);
	initalize_idt_entry(178,interrupt_wrapper_178);
	initalize_idt_entry(179,interrupt_wrapper_179);
	initalize_idt_entry(180,interrupt_wrapper_180);
	initalize_idt_entry(181,interrupt_wrapper_181);
	initalize_idt_entry(182,interrupt_wrapper_182);
	initalize_idt_entry(183,interrupt_wrapper_183);
	initalize_idt_entry(184,interrupt_wrapper_184);
	initalize_idt_entry(185,interrupt_wrapper_185);
	initalize_idt_entry(186,interrupt_wrapper_186);
	initalize_idt_entry(187,interrupt_wrapper_187);
	initalize_idt_entry(188,interrupt_wrapper_188);
	initalize_idt_entry(189,interrupt_wrapper_189);
	initalize_idt_entry(190,interrupt_wrapper_190);
	initalize_idt_entry(191,interrupt_wrapper_191);
	initalize_idt_entry(192,interrupt_wrapper_192);
	initalize_idt_entry(193,interrupt_wrapper_193);
	initalize_idt_entry(194,interrupt_wrapper_194);
	initalize_idt_entry(195,interrupt_wrapper_195);
	initalize_idt_entry(196,interrupt_wrapper_196);
	initalize_idt_entry(197,interrupt_wrapper_197);
	initalize_idt_entry(198,interrupt_wrapper_198);
	initalize_idt_entry(199,interrupt_wrapper_199);
	initalize_idt_entry(200,interrupt_wrapper_200);
	initalize_idt_entry(201,interrupt_wrapper_201);
	initalize_idt_entry(202,interrupt_wrapper_202);
	initalize_idt_entry(203,interrupt_wrapper_203);
	initalize_idt_entry(204,interrupt_wrapper_204);
	initalize_idt_entry(205,interrupt_wrapper_205);
	initalize_idt_entry(206,interrupt_wrapper_206);
	initalize_idt_entry(207,interrupt_wrapper_207);
	initalize_idt_entry(208,interrupt_wrapper_208);
	initalize_idt_entry(209,interrupt_wrapper_209);
	initalize_idt_entry(210,interrupt_wrapper_210);
	initalize_idt_entry(211,interrupt_wrapper_211);
	initalize_idt_entry(212,interrupt_wrapper_212);
	initalize_idt_entry(213,interrupt_wrapper_213);
	initalize_idt_entry(214,interrupt_wrapper_214);
	initalize_idt_entry(215,interrupt_wrapper_215);
	initalize_idt_entry(216,interrupt_wrapper_216);
	initalize_idt_entry(217,interrupt_wrapper_217);
	initalize_idt_entry(218,interrupt_wrapper_218);
	initalize_idt_entry(219,interrupt_wrapper_219);
	initalize_idt_entry(220,interrupt_wrapper_220);
	initalize_idt_entry(223,interrupt_wrapper_223);
	initalize_idt_entry(224,interrupt_wrapper_224);
	initalize_idt_entry(225,interrupt_wrapper_225);
	initalize_idt_entry(226,interrupt_wrapper_226);
	initalize_idt_entry(227,interrupt_wrapper_227);
	initalize_idt_entry(228,interrupt_wrapper_228);
	initalize_idt_entry(229,interrupt_wrapper_229);
	initalize_idt_entry(230,interrupt_wrapper_230);
	initalize_idt_entry(231,interrupt_wrapper_231);
	initalize_idt_entry(232,interrupt_wrapper_232);
	initalize_idt_entry(233,interrupt_wrapper_233);
	initalize_idt_entry(234,interrupt_wrapper_234);
	initalize_idt_entry(235,interrupt_wrapper_235);
	initalize_idt_entry(236,interrupt_wrapper_236);
	initalize_idt_entry(237,interrupt_wrapper_237);
	initalize_idt_entry(238,interrupt_wrapper_238);
	initalize_idt_entry(239,interrupt_wrapper_239);
	initalize_idt_entry(240,interrupt_wrapper_240);
	initalize_idt_entry(241,interrupt_wrapper_241);
	initalize_idt_entry(242,interrupt_wrapper_242);
	initalize_idt_entry(243,interrupt_wrapper_243);
	initalize_idt_entry(244,interrupt_wrapper_244);
	initalize_idt_entry(245,interrupt_wrapper_245);
	initalize_idt_entry(246,interrupt_wrapper_246);
	initalize_idt_entry(247,interrupt_wrapper_247);
	initalize_idt_entry(248,interrupt_wrapper_248);
	initalize_idt_entry(249,interrupt_wrapper_249);
	initalize_idt_entry(250,interrupt_wrapper_250);
	initalize_idt_entry(251,interrupt_wrapper_251);
	initalize_idt_entry(252,interrupt_wrapper_252);
	initalize_idt_entry(253,interrupt_wrapper_253);
	initalize_idt_entry(254,interrupt_wrapper_254);
	initalize_idt_entry(255,interrupt_wrapper_255);
}

