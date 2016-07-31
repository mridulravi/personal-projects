(require (lib "plot.ss" "plot"))

(define (makepoint x y)
  (lambda (t)
    (if ( = t 0) x y)
  )
)
(define (x-of point)
  (point 0)
)
(define (y-of point)
  (point 1)
)

(define (draw curve tmin tmax)
  (line
   (lambda (t)
     (vector ((x-of curve) t) ((y-of curve) t))
   )
   (mode `parametric)
   (t-max tmax)
   (t-min tmin)
  )
)

(define (line)
  (define (unitx t) t)
  (define (unity t) (- t))
  (makepoint unitx unity)
)

;(define (translate curve dx dy)
;  (define (unitx t) ( + ((x-of curve) t) dx))
;  (define (unity t) ( + ((y-of curve) t) dy))
;  (makepoint unitx unity)
;)

;procedure to plot a curve
(define (myplot curve tmin tmax)
  (plot (draw curve tmin tmax)
        (y-max 10)
        (y-min -10)
  )
)

;procedure to connect ends
(define (connect-ends curve1 curve2)
  (define (unitx t)
    (if ( < t ( / 1 2)) ((x-of curve1) t)
        ((x-of (translate curve2 (-((x-of curve1) 0.5)((x-of curve2) 0.5)) (-((y-of curve1) 0.5)((y-of curve2) 0.5)))) t)
    )
  )
  (define (unity t)
    (if ( < t ( / 1 2)) ((y-of curve1) t)
        ((y-of (translate curve2 (-((x-of curve1) 0.5) ((x-of curve2) 0.5)) (-((y-of curve1) 0.5)((y-of curve2) 0.5)))) t)
    )
  )
  (makepoint unitx unity)
)

;procedure to connect ends version 2
(define (connect-ends2 curve1 curve2)
  (define (unitx t)
    (if ( < t 4) ((x-of curve1) t)
        ((x-of (translate curve2 (-((x-of curve1) 4)((x-of curve2) 0)) (-((y-of curve1) 4)((y-of curve2) 0)))) ( - t 4))
     )
  )
  (define (unity t)
    (if ( < t 4) ((y-of curve1) t)
        ((y-of (translate curve2 (-((x-of curve1) 4) ((x-of curve2) 0)) (-((y-of curve1) 4)((y-of curve2) 0)))) ( - t 4))
    )
  )
  (makepoint unitx unity)
)


;procedure to draw image in y-axis
(define (reflect-through-y-axis curve)
    (define (unitx t) ( - ((x-of curve) t)))
  (define (unity t) ((y-of curve) t))
    (makepoint unitx unity)
)

;procedure to rotate curve
(define (rotate-around-origin curve radian)
  (define (unitx t) (+  ( * (cos radian) (( x-of curve) t)) ( *(sin radian) ((y-of curve) t))))
  (define (unity t) ( - ( * (cos radian) ((y-of curve) t)) (* (sin radian) ((x-of curve)t))))
  (makepoint unitx unity)
)

;procedure to translate
(define (translate curve dx dy)
  (define (unitx t) ( + ((x-of curve) t) dx))
  (define (unity t) ( + ((y-of curve) t) dy))
  (makepoint unitx unity)
)

;procedure to zoom
(define (scale-x-y  curve xfac yfac)
  (define (unitx t) (* ((x-of curve) t) xfac))
  (define (unity t) (* ((y-of curve) t) yfac))
  (makepoint unitx unity)
)

;curve to draw vertical line
(define (vertical-line x y l)
  (define (unitx t) x)
  (define (unity t)  (+ t y))
  (plot (draw (makepoint unitx unity) 0 l)
       (y-max (+ y l 10))
  )
)

;draws a vrtical line at any given x-co-ordinate
(define (vertical-line-at x)
  (define (unitx t) x)
  (define (unity t) t)
  (makepoint unitx unity)
)
;curve to draw parabola
(define (parabola)
  (define (unity t) (* t t))
  (define (unitx t) t)
  (makepoint unitx unity)
)

(define (vert-line x y)
  (define (unitx t) x)
  (define (unity t) (+ y t))
  (makepoint unitx unity)
)
(define (hor-line x y)
  (define (unitx t ) t)
  (define (unity t) y)
  (makepoint unitx unity)
)


(define (connect-ends3 curve1 x1 y1 x2 y2)
  (define (unitx t) 
    (if (< t x2) ((x-of curve1) t)
        ((x-of (translate curve2 (- ((x-of curve2)x2) ((x-of curve1)t)) (- ((y-of curve2)x2) ((y-of curve1)t)))) t)