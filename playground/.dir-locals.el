((nil
  (eval add-hook 'after-save-hook
        (lambda (&rest args)
          (when (and (boundp 'my-auto-commit) my-auto-commit)
            (let ((async-shell-command-buffer 'confirm-kill-process)
                  (display-buffer-alist (cons '("\\*Async Shell Command\\*" (display-buffer-no-window)) display-buffer-alist)))
              (async-shell-command (format "git add %s && git commit --amend -m 'wip' && git push --force-with-lease origin" (file-relative-name (buffer-file-name))))))) nil t) ))
