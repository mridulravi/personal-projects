#lang racket
;A particle is far from a centroid if 
;d = distance from line particle to the line centroid
;s = length of the line side of the region
;d/s > theta
(define iter 1000)
(define theta 0.5)



;(define (main l)
;  (define (main-helper lnow i)
;    (if (= i iter) exit
;        (begin
;          (draw lnow)
;          (let ([lnext (singleStep lnow)])
;            (main-helper lnext (+ i 1))))))
;  (main-helper initialList 0))


;Use the following structs to represent bodies, squares and positions:
(struct body (mass posn velocity) #:transparent)
(struct gnode (mass posn subtrees) #:transparent)
(struct box (llx lly rux ruy) #:transparent)
(struct vec (x y) #:transparent)

(define initialArea (box 0 0 10.0 10.0))

;(define (singleStep bodies)
;  (let* ([tree (buildTree initialArea bodies)]
;         [forces (calcForces initialArea tree bodies)])
;    (movebodies bodies forces)))
(define b1 (body 1 (vec 0 0) (vec 9 0)))
(define b2 (body 4 (vec 10 10) (vec 8 7)))

(define (distance b1 b2)
  (sqrt (+ 
   (expt (- (vec-x (body-posn b1)) (vec-x (body-posn b2))) 2)
   (expt (- (vec-x (body-posn b1)) (vec-x (body-posn b2))) 2))))

(define (are-near? b1 b2 square)
  (let ((d (distance b1 b2))
        (s (abs (- (box-llx square) (box-rux square)))))
    (if (< (/ s d) theta)
        #f
        #t)))

(define (buildTree area bodies)
  (let* (lu (box-llx area) (box-lly area) rux ruy)
          