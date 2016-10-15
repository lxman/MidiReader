#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum { sequence_no, text, copy_not, inst_name, text_lyric, text_mark,
			   cue_point, chan_prefix, eot, set_tempo, smpte_offset, time_sig,
			   key_sig, seq_spec, seq_name, note_off, note_on, poly_key,
			   cnt_change, pgm_change, chan_press, pw_change, sys_ex, song_ptr,
			   song_sel, tune_req, eoe, tim_clk, start, cont, stop, act_sens,
			   rst, port_sel
			 } EventType;

typedef enum { bank_sel1, mod_wheel1, brth_ctl1, undef1, foot_cnt1, port_time1, data_ent1,
			   chan_vol1, balance1, undef2, pan1, exp_ctl1, eff_ctl1_1, eff_ctl2_1, undef3,
			   undef4, gp_ctl1_1, gp_ctl2_1, gp_ctl3_1, gp_ctl4_1, undef5, undef6, undef7, undef8,
			   undef9, undef10, undef11, undef12, undef13, undef14, undef15, undef16,
			   bank_sel2, mod_wheel2, brth_ctl2, undef17, foot_cnt2, port_time2, data_ent2,
			   chan_vol2, balance2, undef18, pan2, exp_ctl2, eff_ctl1_2, eff_ctl2_2, undef19,
			   undef20, gp_ctl1_2, gp_ctl2_2, gp_ctl3_2, gp_ctl4_2, undef21, undef22, undef23,
			   undef24, undef25, undef26, undef27, undef28, undef29, undef30, undef31, undef32,
			   damp_ped, port_ped, sus_ped, soft_ped, leg_ped, hold_2, sound_1, sound_2, sound_3,
			   sound_4, sound_5, sound_6, sound_7, sound_8, sound_9, sound_10, gp_ctl5, gp_ctl6,
			   gp_ctl7, gp_ctl8, port_ctl, undef33, undef34, undef35, undef36, undef37, undef38,
			   eff1_dep, eff2_dep, eff3_dep, eff4_dep, eff5_dep, de_inc, de_dec, nr_lsb, nr_msb,
			   rp_lsb, rp_msb, undef39, undef40, undef41, undef42, undef43, undef44, undef45,
			   undef46, undef47, undef48, undef49, undef50, undef51, undef52, undef53, undef54,
			   undef55, all_off, reset_all, local_off, all_notes_off, omni_off, omni_on,
			   poly_toggle, poly_on } CtrlMsg;

typedef struct {
		int num;
		int den;
		int met;
		int note_rat;
} timeSig;

typedef struct {
		int key;
		bool major;
} kSig;

#endif // GLOBALS_H

