#lang racket

; From Lab 1
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



; DEFAULT PARMS
(define (default-parms f values)
    (lambda args 
        (if (< (length args) (length values))
            (apply 
                f 
                (append args 
                    (list-tail values (length args))))
            (apply f args)
        )
    )
)


; TYPE PARMS
(define (type-parms f types)
    (lambda args 
        (if (foldr 
                (lambda (x y) 
                    (and x y)) 
                #t 
                (map (lambda (x y) (y x) ) args types))
            (apply f args)
            (error "got an error"))))

; NEW SIN 2
(define new-sin2 (default-parms
            (type-parms
             new-sin
             (list number? symbol?)) 
            (list 0 'radians)))
