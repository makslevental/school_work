	(setq package-archives '(("gnu" . "http://elpa.gnu.org/packages/")
                         ("marmalade" . "http://marmalade-repo.org/packages/")
                         ("melpa" . "http://melpa.milkbox.net/packages/")))

(let ((default-directory "~/.emacs.d/elpa/"))

(load-file "~/.emacs.d/themes/monokai-theme.el")
;; doesn't cooperate with cedet
;;(load-file "~/.emacs.d/elpa/smooth-scrolling/smooth-scroll.el")
(load-file "cedet/cedet-config.el")
(setq scroll-step 1)
(add-to-list 'load-path (expand-file-name
      "~/.emacs.d/elpa/ecb/"))
(require 'ecb)
(add-to-list 'load-path (expand-file-name
      "~/.emacs.d/elpa/multiple-cursors/"))
(load-file "multiple-cursors/multiple-cursors.el")
(require 'multiple-cursors)
(normal-top-level-add-to-load-path '("auto-complete" "popup")))
 
(require 'auto-complete)
(require 'popup)
(require 'multiple-cursors)
;;(require 'smooth-scroll)
(delete-selection-mode 1)
(global-linum-mode t)
(global-auto-complete-mode t)
;;(global-show-paren-mode t)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ecb-options-version "2.40")
 '(ede-project-directories (quote ("/tmp/myproject/src" "/tmp/myproject/include" "/tmp/myproject" "/home/max" "/home/max/Desktop/school_work/emacs"))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(setq debug-on-error t)

(global-set-key (kbd "C-k") 'kill-buffer)
(global-set-key (kbd "<C-tab>") 'other-window)

(setenv "PATH" (concat (getenv "PATH") ":/usr/local/MATLAB/MATLAB_Production_Server/R2013a/bin"))
(setq exec-path (append exec-path '("/usr/local/MATLAB/MATLAB_Production_Server/R2013a/bin")))

;; Setting up matlab-mode
(add-to-list 'load-path "~/.emacs.d/elpa/matlab-emacs")
	(load-library "matlab-load")
(matlab-cedet-setup)
;;(custom-set-variables
;; '(matlab-shell-command-switches '("-nodesktop -nosplash")))
(add-hook 'matlab-mode-hook 'auto-complete-mode)
(setq auto-mode-alist
    (cons
     '("\\.m$" . matlab-mode)
     auto-mode-alist))