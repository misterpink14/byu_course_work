#lang racket

(define (sum-coins pennies nickels dimes quarters)
  (+
   pennies
   (+
    (* nickels 5)
    (+ (* dimes 10) (* quarters 25) ))))


(define (degrees-to-radians angle)
  (*
   pi
   (/ angle 180)))


(define (sign x)
  (cond
    [(negative? x) -1]
    [(positive? x) 1]
    (else 0)))

(define (new-sin angle type)
  (sin (if (symbol=? type 'degrees) (degrees-to-radians angle) angle)))
