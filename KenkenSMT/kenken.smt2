;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	Author: Jakub Taraska
;	I grant permission to use this for research purposes. 
;	running time:  0m 0.031s
;	1994 MiB System memory
;	Intel Xeon W3503 (2.40 GHz) CPU
;
;	Below is a SMT model for a 4x4 ken-ken puzzle, where the general rules of the
;	puzzle are:
;	1- all rows and columns must hold distinct values, ranging from 1 to 4
;	2- cages exist that hold mathematical rules for the values within them. A 
;	solution must satisfy these rules in order to be a valid solution. 
;
;	The puzzel being moddeled can be found at http://www.kenkenpuzzle.com/game
;	With puzzel number 151803.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(set-option :produce-assignments true)
(set-logic QF_LIA)

;(declare-const xx Int) is equivalent to (declare-fun xx() Int ) 

(declare-const aa Int)
(declare-const ab Int)
(declare-const ac Int)
(declare-const ad Int)

(declare-const ba Int)
(declare-const bb Int)
(declare-const bc Int)
(declare-const bd Int)

(declare-const ca Int)
(declare-const cb Int)
(declare-const cc Int)
(declare-const cd Int)

(declare-const da Int)
(declare-const db Int)
(declare-const dc Int)
(declare-const dd Int)

(assert (and (> aa 0) (< aa 5)))
(assert (= ab 1))
(assert (and (> ac 0) (< ac 5)))

(assert (and (> ba 0) (< ba 5)))
(assert (and (> bb 0) (< bb 5)))
(assert (and (> bc 0) (< bc 5)))
(assert (and (> bd 0) (< bd 5)))

(assert (and (> ca 0) (< ca 5)))
(assert (and (> cb 0) (< cb 5)))
(assert (and (> cc 0) (< cc 5)))
(assert (and (> cd 0) (< cd 5)))

(assert (and (> da 0) (< da 5)))
(assert (and (> db 0) (< db 5)))
(assert (= dc 4))
(assert (and (> dd 0) (< dd 5)))

(assert (distinct aa ab ac ad))			        ;the first row is distinct
(assert (distinct ba bb bc bd))			        ;the second row is distinct
(assert (distinct ca cb cc cd))			        ;the third row is distinct
(assert (distinct da db dc dd))			        ;the last row is distinct

(assert (distinct aa ba ca da))			        ;the first column is distinct
(assert (distinct ab bb cb db))			        ;the second column is distinct
(assert (distinct ac bc cc dc))			        ;the third column is distinct
(assert (distinct ad bd cd dd))			        ;the last column is distinct

(assert (or (=(- aa ba) 1) (= (- ba aa) 1)))		;aa - ba = 1 || ba - aa = 1
(assert (or (= ac (* ad 2))(= ad (* ac 2)))) 		;ac = 2 * ad || ac = 2 * ad
(assert (or (=(- bb bc) 3) (= (- bc bb) 3)))		;bb - bc = 3 || bc - bb = 3
(assert (= (+ ca cb cc) 9))                             ;ca + cb + cc = 9
(assert (or (=(- da db) 2) (= (- db da) 2)))		;da - db = 2 || db - da = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	(assert (= 6 (* bd cd dd)))   nonlinear arithmetic, can be replaced
;	since 4 is not a factor of 3, the possibilities of bd, cd, and dd are reduced
;	to 1, 2, and 3, irrespectively. For any values that they take, the constraint
;	6 = bd * cd * dd will hold, so it is sufficient to say ad = 4, and remaining
;	values are distinct.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(assert (= ad 4)) 		

(check-sat)         	
(get-value (aa ab ac ad))
(get-value (ba bb bc bd))
(get-value (ca cb cc cd))
(get-value (da db dc dd))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	EXPECTED OUTPUT
;	sat
;	((aa 3)(ab 1)(ac 2)(ad 4))
;	((ba 2)(bb 4)(bc 1)(bd 3))
;	((ca 4)(cb 2)(cc 3)(cd 1))
;	((da 1)(db 3)(dc 4)(dd 2))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	this following line checks if there could be a different ordering of the cage
;	{bd, cd, dd}, or the cage {ca, cb, cc}. Other blocks are too easy to derive 
;	definite answers for, such as {ac, ad} where ad must be 4, so ac must be 2.
;	uncomment the following two lines and comment out the above (check-sat) to
;	prove uniqueness. 
;
;	(assert (or (= cd 2)(= bd 2)(= cc 2)(= ca 2)))
;	(check-sat)
;
;	EXPECTED OUTPUT
;	unsat
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

