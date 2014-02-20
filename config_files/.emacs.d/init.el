(load-file "~/.emacs.d/themes/monokai-theme.el")
(setq package-archives '(("gnu" . "http://elpa.gnu.org/packages/")
                         ("marmalade" . "http://marmalade-repo.org/packages/")
                         ("melpa" . "http://melpa.milkbox.net/packages/")))

(let ((default-directory "~/.emacs.d/elpa/"))

(normal-top-level-add-to-load-path '("auto-complete" "popup")))
 
(require 'auto-complete)
(require 'popup)

(delete-selection-mode 1)
(global-linum-mode t)
(global-auto-complete-mode t)
;;(global-show-paren-mode t)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(inhibit-startup-screen t))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
