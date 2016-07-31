#lang racket
(require "declarations.ss")
(provide testList1 testList2 testList3  testList4  )
    (define testList1

         (list

          (particle 5000.0 (vec 300 500) (vec 0.0 0.0))

          (particle 40.0 (vec 100 500) (vec 0.0 0.0))  

          (particle 200.0 (vec 500 500) (vec 0.0 0.0))))

;And these are the expected output values
;
;(#(struct:vec 10719.706129879343 0.0)
;
; #(struct:vec 1231.5616880099844 0.0)
;
; #(struct:vec -11951.267817889327 0.0))

(define testList2

         (list

           (particle 40.0 (vec 300 600) (vec 30.0 0.0))

           (particle 5000.0 (vec 300 500) (vec 0.0 0.0))

           (particle 10.0 (vec  300 300) (vec -20 0.0))

           (particle 40.0 (vec 300 250.0) (vec -20 0.0))

           (particle 50.0 (vec 100 500) (vec 0 -20))

           (particle 10.0 (vec 400 500) (vec 0.0 15))

           (particle 50.0 (vec 300 650) (vec 25 0.0))

           (particle 10.0 (vec 300 100) (vec 15 0))

           (particle 7.0 (vec 200 500) (vec 0.0 -20))

           (particle 5.0 (vec 300 90) (vec 5 0.0))))

;And these are the expected output values
;
;(#(struct:vec -84.01855024080207 504.80636476929095)
;
; #(struct:vec 126.826290470051 -676.5969583622859)
;
; #(struct:vec 21.942961517725678 11.678426547961955)
;
; #(struct:vec 44.045859372478134 39.387980549837096)
;
; #(struct:vec 54.85720826302568 100.6496587532947)
;
; #(struct:vec -26.573522361146455 14.041959458996724)
;
; #(struct:vec -188.98762481936916 15.855775250591961)
;
; #(struct:vec -2.1001280378357974 5.342088882353876)
;
; #(struct:vec 54.45569399080102 -18.453562764180933)
;
; #(struct:vec -0.45574404428841003 3.2880427627822892))

(define testList3

          (list

           (particle 10.0 (vec 300 600) (vec 30.0 0.0))

           (particle 80.0 (vec 450 500) (vec 0 -20.0))

           (particle 30.0 (vec 200 580) (vec 10.0 20.0))

           (particle 40.0 (vec 250 400) (vec 20.0 -10.0))

           (particle 50.0 (vec 320 400) (vec 20.0 10.0))

           (particle 5000.0 (vec 300 500) (vec 0.0 0.0))

           (particle 10.0 (vec 80 230) (vec 20 0.0))

           (particle 200.0 (vec 80 200) (vec 10.0 0.0))))

;And these are the expected output values
;
;(#(struct:vec -12.836030217377232 89.54840300504456)
;
; #(struct:vec 489.5960052935118 720.5718989944704)
;
; #(struct:vec -286.98224494809307 -192.79949170545657)
;
; #(struct:vec 644.6062991384551 -217.5456129809952)
;
; #(struct:vec 144.51701060664664 420.43009871727105)
;
; #(struct:vec -1068.158208871288 -1054.4513318726579)
;
; #(struct:vec 53.938553554374764 -8.554253807194776)
;
; #(struct:vec 35.13475196705548 242.50113781718161))

    (define testList4

 (list

  (particle 500 (vec 300 300) (vec 18 12))

  (particle 500 (vec 500 300) (vec -14 10))

  (particle 500 (vec 300 500) (vec 10 -16))

  (particle 500 (vec 500 500) (vec -10 -14))))

;And these are the expected output values
;
;(#(struct:vec -1483.3998812933505 -6277.135930510287)
;
;#(struct:vec 1411.6211794858282 6055.13226231788)
;
;#(struct:vec 605.8461974714442 -267.0224633894836)
;#(struct:vec -534.0674956639216 489.02613158189047))