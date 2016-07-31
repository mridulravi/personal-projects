 #lang racket
(require "declarations.ss")
(require "drawing-routine.ss")
(require "testcases.ss")


; singlestep computes one step of the simulation
(define (singlestep particles)
  (let* ([initialArea (bounding-box particles)]
         [tree (buildTree initialArea particles)] 
         [llx (bbox-llx initialArea)] 
         [rux (bbox-rux initialArea)]
         [forces (calcForces initialArea tree particles)])
    (moveparticles particles forces)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;calcForces calculates  the force on  each particle, given a  tree and
;the initial area in the form of bounding box.

(define (calcForces initialarea tree ps)
  ...)

;moveParticles calculates  the new particle configuration  from a list
;of forces and the initial configuration.
(define (moveparticles ps fs)
  ...)

;;buidTree creates the tree of centroids

(define (buildTree bbox l)
  ...)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;main  will  send the  current  particle  configuration for  printing;
;calculate new configuration and recurse

(define (main ps)
  (define (main-helper ps i)
    (cond [(> i iter) (display "Done")]
          [else (let*
                    ([ps-next (singlestep ps)])
                  (if (= (remainder iter drawtime) 0)
                      (begin 
                        (draw-particles ps)
                        (main-helper ps-next (+ i 1)))
                      (main-helper ps-next (+ i 1))))]))
    (main-helper ps 0))

(main testList1)
;(main testList2)












