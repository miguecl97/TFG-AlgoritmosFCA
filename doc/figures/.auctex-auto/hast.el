(TeX-add-style-hook
 "hast"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("standalone" "rgb")))
   (TeX-run-style-hooks
    "latex2e"
    "figConfig"
    "standalone"
    "standalone10"))
 :latex)

