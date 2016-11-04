#lang racket

; CHECK TEMPS
(define (check-temps temps low high) 
    (foldr 
        (lambda (x y) (and (and (>= x low) (<= x high)) y))
        true 
        temps))


; CHECK TEMPS 1
(define (check-temps1 temps)
  (check-temps temps 5 95))

; convert
(define (convert digits)
  (foldr
    (lambda (x y) (+ x (* 10 y)))
    0
    digits))


; CONVERT F to C
(define (convertFC temps)
  (map
    (lambda (x) (* (/ 5 9) (- x 32)))
    temps))


; DUPLE
(define (duple lst)
  (map
    (lambda (x) (list x x))
    lst))


; AVERAGE
(define (average lst)
  (/ 
    (foldr
      (lambda (x y) (+ x y))
      0
      lst)
    (foldr
      (lambda (x y) (+ y 1))
      0
      lst)))


; ELIMINATE LARGER
(define (eliminate-larger lst)
  (foldr
    (lambda (x y) 
      (if (empty? y)
        (list x)
        (if (< x (last y))
          (append (list x) y)
          y)))
    empty
    lst))


; CURRY2
(define (curry2 func)
  (lambda (x) (lambda (y) (func x y))))

