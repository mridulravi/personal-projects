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
  (if (null? ps)
      '()
      (cons (calcForces-helper initialarea tree (car ps))
            (calcForces initialarea tree (cdr ps)))))

(define (calcForces-helper area tree puc)
  (let* ((s (- (bbox-rux area) (bbox-llx area)))
         (first-c (cond [(gnode? tree) (gnode-posn tree)]
                        [(particle? tree) (particle-posn tree)]))
         (second-c (particle-posn puc))
         (d (distance first-c second-c)))
    (cond [(> (/ d s) theta) (force tree puc)]
          [(and (<= (/ d s) theta) (particle? tree)) (force tree puc)]
          [(and (<= (/ d s) theta) (gnode? tree))
           (let* ((llx (bbox-llx area))
                  (lly (bbox-lly area)) 
                  (rux (bbox-rux area)) 
                  (ruy (bbox-ruy area)) 
                  (lu (bbox llx 
                            (+ lly (/ (- ruy lly) 2))
                            (+ llx (/ (- rux llx) 2))
                            ruy))
                  (ru (bbox (+ llx (/ (- rux llx) 2)) 
                            (+ lly (/ (- ruy lly) 2))
                            rux
                            ruy))
                  (ll (bbox llx 
                            lly
                            (+ llx (/ (- rux llx) 2))
                            (+ lly (/ (- ruy lly) 2))))
                  (rl (bbox (+ llx (/ (- rux llx) 2))
                            lly
                            rux
                            (+ lly (/ (- ruy lly) 2)))))
             (addForces (calcForces-helper lu (car (gnode-subtrees tree)) puc)
                        (calcForces-helper ru (cadr (gnode-subtrees tree)) puc)
                        (calcForces-helper ll (car (cddr (gnode-subtrees tree))) puc)
                        (calcForces-helper rl (cadr (cddr (gnode-subtrees tree))) puc)))])))

(define (distance first-c second-c)
  (sqrt (+ 
   (expt (- (vec-x first-c) (vec-x second-c)) 2)
   (expt (- (vec-y first-c) (vec-y second-c)) 2))))

(define (force by on)
  (let* ((m1 (cond [(gnode? by) (gnode-mass by)]
                   [(particle? by) (particle-mass by)]))
         (m2 (particle-mass on))
         (r1 (cond [(gnode? by) (gnode-posn by)]
                   [(particle? by) (particle-posn by)]))
         (r2 (particle-posn on))
         (r1-x (vec-x r1))
         (r2-x (vec-x r2))
         (r1-y (vec-y r1))
         (r2-y (vec-y r2))
         (r (distance r1 r2))
         (magnitude
          (if (= 0 r)
              0
              (/ (* g m1 m2) (* r r))))
         (direction 
          (if (= 0 r)
              (vec 0 0)
              (vec (/ (- r1-x r2-x) (sqrt (+ (expt (- r1-x r2-x) 2)
                                             (expt (- r1-y r2-y) 2))))
                   (/ (- r1-y r2-y) (sqrt (+ (expt (- r1-x r2-x) 2)
                                             (expt (- r1-y r2-y) 2))))))))                                                
    (vec (* magnitude (vec-x direction)) (* magnitude (vec-y direction)))))

(define (addForces f1 f2 f3 f4)
  (vec (+ (vec-x f1) (vec-x f2) (vec-x f3) (vec-x f4))
       (+ (vec-y f1) (vec-y f2) (vec-y f3) (vec-y f4))))
             
         

;moveParticles calculates  the new particle configuration  from a list
;of forces and the initial configuration.
(define (moveparticles ps fs)
  (zipwith move-single fs ps))

(define (move-single F p)
  (let* ((m (particle-mass p))
         (pos (particle-posn p))
         (u (particle-velocity p))
         (a (vec (/ (vec-x F) m)
                 (/ (vec-y F) m)))
         (t timeslice))    
    (particle m
              (vec (+ (vec-x pos) (+ (* (vec-x u) t) (* 0.5 t t (vec-x a))))
                   (+ (vec-y pos) (+ (* (vec-y u) t) (* 0.5 t t (vec-y a)))))
              (vec (+ (vec-x u) (* (vec-x a) t))
                   (+ (vec-y u) (* (vec-y a) t))))))
            

;;buidTree creates the tree of centroids

(define (buildTree box l)
  (cond [(more-than-1 box l)
         (let* ((llx (bbox-llx box))
                (lly (bbox-lly box)) 
                (rux (bbox-rux box)) 
                (ruy (bbox-ruy box)) 
                (lu (bbox llx 
                          (+ lly (/ (- ruy lly) 2))
                          (+ llx (/ (- rux llx) 2))
                          ruy))
                (ru (bbox (+ llx (/ (- rux llx) 2)) 
                          (+ lly (/ (- ruy lly) 2))
                          rux
                          ruy))
                (ll (bbox llx 
                          lly
                          (+ llx (/ (- rux llx) 2))
                          (+ lly (/ (- ruy lly) 2))))
                (rl (bbox (+ llx (/ (- rux llx) 2))
                          lly
                          rux
                          (+ lly (/ (- ruy lly) 2))))
                (lu-tree (buildTree lu l))
                (ru-tree (buildTree ru l))
                (ll-tree (buildTree ll l))
                (rl-tree (buildTree rl l))
                (mass-lu-tree 
                 (cond [(gnode? lu-tree) (gnode-mass lu-tree)]
                       [(particle? lu-tree) (particle-mass lu-tree)]))
                (mass-ru-tree 
                 (cond [(gnode? ru-tree) (gnode-mass ru-tree)]
                       [(particle? ru-tree) (particle-mass ru-tree)]))
                (mass-ll-tree 
                 (cond [(gnode? ll-tree) (gnode-mass ll-tree)]
                       [(particle? ll-tree) (particle-mass ll-tree)]))
                (mass-rl-tree 
                 (cond [(gnode? rl-tree) (gnode-mass rl-tree)]
                       [(particle? rl-tree) (particle-mass rl-tree)]))
                (posn-lu-tree 
                 (cond [(gnode? lu-tree) (gnode-posn lu-tree)]
                       [(particle? lu-tree) (particle-posn lu-tree)]))
                (posn-ru-tree 
                 (cond [(gnode? ru-tree) (gnode-posn ru-tree)]
                       [(particle? ru-tree) (particle-posn ru-tree)]))
                (posn-ll-tree 
                 (cond [(gnode? ll-tree) (gnode-posn ll-tree)]
                       [(particle? ll-tree) (particle-posn ll-tree)]))
                (posn-rl-tree 
                 (cond [(gnode? rl-tree) (gnode-posn rl-tree)]
                       [(particle? rl-tree) (particle-posn rl-tree)]))
                (main-mass (+ mass-lu-tree
                              mass-ru-tree
                              mass-ll-tree
                              mass-rl-tree))
                (main-posn-x (/ (+ (* mass-lu-tree (vec-x posn-lu-tree))
                                   (* mass-ru-tree (vec-x posn-ru-tree))
                                   (* mass-ll-tree (vec-x posn-ll-tree))
                                   (* mass-rl-tree (vec-x posn-rl-tree)))
                                main-mass))
                (main-posn-y (/ (+ (* mass-lu-tree (vec-y posn-lu-tree))
                                   (* mass-ru-tree (vec-y posn-ru-tree))
                                   (* mass-ll-tree (vec-y posn-ll-tree))
                                   (* mass-rl-tree (vec-y posn-rl-tree)))
                                main-mass))
                (main-posn (vec main-posn-x main-posn-y))
                (main-subtree (list lu-tree ru-tree ll-tree rl-tree)))
           (gnode main-mass main-posn main-subtree))]
        [(exactly-1 box l)
         (let* ((mass-single-particle (particle-mass (lies-inside box l)))
                (posn-single-particle (particle-posn (lies-inside box l))))
           (particle mass-single-particle 
                     posn-single-particle 
                     '()))]
        [else 
         (particle 0
                    (vec (/ (+ (bbox-llx box)
                               (bbox-rux box)) 2)
                         (/ (+ (bbox-lly box)
                               (bbox-ruy box)) 2))
                   (vec 0 0))]))

(define (more-than-1 box l)
  (if (> (count 0 box l) 1)
      #t
      #f))

(define (exactly-1 box l)
  (if (= (count 0 box l) 1)
      #t
      #f))

(define (lies-inside box l)
  (let* ((rux (bbox-rux box))
         (ruy (bbox-ruy box))
         (llx (bbox-llx box))
         (lly (bbox-lly box)))
    (if (and (and (< (vec-x (particle-posn (car l))) rux)
                     (>= (vec-x (particle-posn (car l))) llx))
                (and (< (vec-y (particle-posn (car l))) ruy)
                     (>= (vec-y (particle-posn (car l))) lly)))
        (car l)
        (lies-inside box (cdr l)))))

(define (count n box l)
  (let* ((rux (bbox-rux box))
         (ruy (bbox-ruy box))
         (llx (bbox-llx box))
         (lly (bbox-lly box)))
    (cond [(null? l) n]
          [(and (and (< (vec-x (particle-posn (car l))) rux)
                     (>= (vec-x (particle-posn (car l))) llx))
                (and (< (vec-y (particle-posn (car l))) ruy)
                     (>= (vec-y (particle-posn (car l))) lly)))
           (count (+ n 1) box (cdr l))]
          [else (count n box (cdr l))])))

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

(main testList2)










