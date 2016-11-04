#lang racket

; CHECK TEMPS 1
(define (check-temps1 temps)
  (check-temps temps 5 95))


; CHECK TEMPS
(define (incl-range value lower upper)
  (if (and (>= value lower) (<= value upper))
    true
    false))

(define (check-temps temps low high)
  (if (empty? temps)
    true
    (if (incl-range (first temps) low high)
      (check-temps (rest temps) low high)
      false)))


; CONVERT
(define (convert digits)
  (if (empty? digits)
    0
    (+ (first digits) (* 10 (convert (rest digits))))))

; DUPLE
(define (duple lst)
  (if (empty? lst)
    empty
    (append (list (list (first lst) (first lst))) (duple (rest lst)))))


; AVERAGE
(define (len lst)
  (if (empty? lst)
    0
    (+ 1 (len (rest lst)))))

(define (total lst)
  (if (empty? lst)
    0
    (+ (first lst) (total (rest lst)))))

(define (average lst)
  (if (empty? lst)
    0
    (/ (total lst) (len lst))))


; CONVERT F to C
(define (fc temp)
  (* (/ 5 9) (- temp 32)))

(define (convertFC temps)
  (if (empty? temps)
    empty
    (append (list (fc (first temps))) (convertFC (rest temps)))))


; ELIMINATE LARGER
(define (get-max lst val)
  (if (empty? lst)
    val
    (if (empty? val) 
      (get-max (rest lst) (first lst))
      (if (> (first lst) val)
        (get-max (rest lst) (first lst))
        (get-max (rest lst) val)
      )
    )
  )
)

(define (elim-lgr lst rm)
  (if (empty? lst)
    empty
    (if (= (first lst) rm)
      (elim-lgr (rest lst) rm)
      (append (list (first lst)) (elim-lgr (rest lst) rm))
    )
  )
)

(define (eliminate-larger lst)
  (elim-lgr lst (get-max lst empty)))


; GET NTH
(define (get-nth lst n)
  (if (= n 0)
    (first lst)
    (get-nth (rest lst) (- n 1))
  )
)


; FIND ITEM
(define (f-item lst target key) 
  (if (empty? lst)
    -1
    (if (= (first lst) target)
      key
      (f-item (rest lst) target (+ key 1))
    )
  )
)

(define (find-item lst target)
  (f-item lst target 0)
)


(find-item (list 1 2 3 4) 43)
 
