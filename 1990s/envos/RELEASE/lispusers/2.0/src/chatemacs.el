;; GNU Emacs code for Interlisp-D mouse using CHATEMACS.
;; Copyright (C) Free Software Foundation March 1987.

;; This file is part of GNU Emacs.

;; GNU Emacs is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY.  No author or distributor
;; accepts responsibility to anyone for the consequences of using it
;; or for whether it serves any particular purpose or works at all,
;; unless he says so in writing.  Refer to the GNU Emacs General Public
;; License for full details.

;; Everyone is granted permission to copy, modify and redistribute
;; GNU Emacs, but only under the conditions described in the
;; GNU Emacs General Public License.   A copy of this license is
;; supposed to have been given to you along with GNU Emacs so you
;; can know your rights and responsibilities.  It should be in a
;; file named COPYING.  Among other things, the copyright notice
;; and this notice must be preserved on all copies.


;;;  Original version by John Robinson (jr@bbn-unix.arpa, bbncca!jr), Oct 1985
;;;  Adapted from code for BBN Bitgraph by Randy Gobbel, March 1987

;;;  User customization option:

(defconst shift 1)
(defconst control 2)
(defconst shift-control 3)
(defconst meta 4)

(defconst left 4)
(defconst middle 1)
(defconst right 2)

(defvar il-mouse-kill-emacs
  (symbol-function 'kill-emacs))
(defvar il-mouse-fast-select-window t
  "*Non-nil for mouse hits to select new window, then execute; else just select.")
(defvar scrollbar-enabled t "Non-nil to use last column as scrollbar")
(defvar auto-switch-enabled nil "Non-nil to send init string to terminal")
(defvar save-screen-width (screen-width))
(defvar save-screen-height (screen-height))

;;;  Defuns:

(defun il-mouse-report ()
  "Read Interlisp ChatEmacs mouse report, branch to appropriate sub-handler."
  (interactive)
  (let ((sub-char (read-char)))
    (cond
     ((= sub-char ?s) (il-set-screen-size))
     ((= sub-char ?m) (il-mouse-command))))
  )

(defun il-set-screen-size ()
  (let ((cur-screen-width (il-get-tty-num ?\;))
	(cur-screen-height (il-get-tty-num ?\;)))
    (or (= cur-screen-width save-screen-width)
	(progn
	  (setq save-screen-width cur-screen-width)
	  (set-screen-width cur-screen-width)))
    (or (= cur-screen-height save-screen-height)
	(progn
	  (setq save-screen-height cur-screen-height)
	  (set-screen-height cur-screen-height)))
    )
  )


(defun il-mouse-command ()
  "Read and parse Interlisp ChatEmacs mouse report, and do what it asks.

L-- move point          *  |---- These apply for mouse click in a window.
--R set mark            *  | If il-mouse-fast-select-window is nil,
-C- depends on shift    *  | just selects that window.

middle-button actions:
   shift: yank region to point
   control: kill region
   shift-control: copy region to killbuffer

    on modeline		    on \"scroll bar\"	in minibuffer
L-- split-vertical	    line to top		execute-extended-command
--R split-horizontal	    line to bottom	eval-expression
-C- delete-window	    goto-char		proportional	suspend-emacs

Meta-mouse-button actions are same as scrollbar."
  (interactive)
  ;;  (il-get-tty-num ?\;)
  (let*
      ((x (min (1- (screen-width))
	       (il-get-tty-num ?\;)))
       (y (min (1- (screen-height))
	       (il-get-tty-num ?\;)))
       (buttons (il-get-tty-num ?\;))
       (bucky-bits (il-get-tty-num ?\;))
       (window (il-pos-to-window x y))
       (edges (window-edges window))
       (old-window (selected-window))
       (in-minibuf-p (eq y (1- (screen-height))))
       (same-window-p (and (not in-minibuf-p) (eq window old-window)))
       (in-modeline-p (eq y (1- (nth 3 edges))))
       (in-scrollbar-p (>= x (1- (nth 2 edges)))))
    (setq x (- x (nth 0 edges)))
    (setq y (- y (nth 1 edges)))
    (cond (in-modeline-p
	   (select-window window)
	   (cond ((= buttons left)
		  (split-window-vertically))
		 ((= buttons right)
		  (delete-window))
		 ((= buttons middle)
		  (split-window-horizontally))))
	  ((or (and scrollbar-enabled in-scrollbar-p)
	       (eq bucky-bits meta))
	   (select-window window)
	   (cond ((= buttons left)
		  (scroll-up y))
		 ((= buttons right)
		  (scroll-down y))
		 ((= buttons middle)
		  (goto-char (* y (/ (- (point-max) (point-min))
				     (1- (window-height)))))
		  (beginning-of-line)
		  (what-cursor-position)))
	   (select-window old-window))
	  (same-window-p (il-button-command x y buttons bucky-bits))
	  (in-minibuf-p
	   (cond ((= buttons middle)
		  (call-interactively 'eval-expression))
		 ((= buttons left)
		  (call-interactively 'execute-extended-command))
		 ((= buttons right)
		  (suspend-emacs))
		 ))
	  (t				;in another window
	   (select-window window)
	   (cond ((not il-mouse-fast-select-window))
		 (t (il-button-command x y buttons bucky-bits)))
	   ))))

(defun il-button-command (x y buttons bucky-bits)
  (cond ((= buttons left)
	 (cond ((eq bucky-bits 0)
		(il-move-point-to-x-y x y))
	       ((eq bucky-bits control)
		(push-mark)
		(il-move-point-to-x-y x y)
		(kill-region (mark) (point)))
	       ((eq bucky-bits shift)
		(copy-region-as-kill (mark) (point))
		(il-move-point-to-x-y x y)
		(setq this-command 'yank)
		(yank))
	       ((eq bucky-bits shift-control)
		(kill-region (mark) (point))
		(il-move-point-to-x-y x y)
		(setq this-command 'yank)
		(yank))
	       )
	 )
;	((= buttons middle)
;	 (cond ((eq bucky-bits 0)
;		(il-move-point-to-x-y x y)
;		(il-balance-beam-word)
;		(mark-word 1))
;	       ((eq bucky-bits control)
;		(il-balance-beam-word)
;		(push-mark)
;		(il-move-point-to-x-y x y)
;		(mark-word 1)
;		(kill-region (mark) (point)))
;	       ((eq bucky-bits shift)
;		(il-move-point-to-x-y x y)
;		(backward-word)
;		(setq this-command 'yank)
;		(yank))
;	       ((eq bucky-bits shift-control)
;		(push-mark)
;		(il-move-point-to-x-y x y)
;		(backward-word)
;		(copy-region-as-kill (mark) (point)))
;	       )
;	 )
	((= buttons right)
	 (push-mark)
	 (il-move-point-to-x-y x y)
	 (if (eq bucky-bits control)
	     (kill-region (mark) (point))
	   (progn
	     (sit-for 1)
	     (exchange-point-and-mark))
	   )
	 )
	)
  )

;(defun il-balance-beam-word ()
;  (let (left-distance left-point right-point (start-point (point)))
;    (save-excursion
;      (backward-word 1)
;      (setq left-point (point))
;      (setq left-distance (- start-point (point)))
;      (forward-word 1)
;      (setq right-point (point)))
;    (if (<= left-distance (- (point) start-point)) left-point right-point)
;    )
;  )

(defun il-get-tty-num (term-char)
  "Read from terminal until TERM-CHAR is read, and return intervening number.
Upon non-numeric not matching TERM-CHAR, signal an error."
  (let
      ((num 0)
       (char (- (read-char) 48)))
    (while (and (>= char 0)
		(<= char 9))
      (setq num (+ (* num 10) char))
      (setq char (- (read-char) 48)))
    (or (eq term-char (+ char 48))
;	(progn
;	  (il-program-mouse)
	  (error "Invalid data format in mouse command"))
    num))

;(defun il-move-point-to-x-y (x y)
;  "Position cursor in window coordinates.
;X and Y are 0-based character positions in the window."
;  (move-to-window-line y)
;  (move-to-column x)
;  )

(defun il-move-point-to-x-y (x y)
  "Move cursor to window location X, Y.
Handles wrapped and horizontally scrolled lines correctly."
  (move-to-window-line y)
  ;; window-line-end expects this to return the window column it moved to.
  (let ((cc (current-column))
	(nc (move-to-column
	     (if (zerop (window-hscroll))
		 (+ (current-column)
		    (min (- (window-width) 2)	; To stay on the line.
			 x))
	       (+ (window-hscroll) -1
		  (min (1- (window-width))	; To stay on the line.
		       x))))))
    (- nc cc)))

(defun il-pos-to-window (x y)
  "Find window corresponding to screen coordinates.
X and Y are 0-based character positions on the screen."
  (let ((edges (window-edges))
	(window nil))
    (while (and (not (eq window (selected-window)))
		(or (<  y (nth 1 edges))
		    (>= y (nth 3 edges))
		    (<  x (nth 0 edges))
		    (>= x (nth 2 edges))))
      (setq window (next-window window))
      (setq edges (window-edges window))
      )
    (or window (selected-window))
    )
  )

(defun suspend-hook-fn ()
  (interactive)
  (send-string-to-terminal "\e0")
  nil
  )

(defun suspend-resume-hook-fn ()
  (interactive)
  (send-string-to-terminal "\e1")
  nil
  )

(global-set-key "\C-\\" 'il-mouse-report)
(if auto-switch-enabled
    (progn
      (send-string-to-terminal "\e1")
      (defun kill-emacs ()
	(interactive)
	(send-string-to-terminal "\e0")
	(funcall il-mouse-kill-emacs)
	)
      (setq suspend-hook (symbol-function 'suspend-hook-fn))
      (setq suspend-resume-hook (symbol-function 'suspend-resume-hook-fn))
      )
  )
