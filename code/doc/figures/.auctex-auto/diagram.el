(TeX-add-style-hook
 "diagram"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("standalone" "rgb")))
   (TeX-run-style-hooks
    "latex2e"
    "figConfig"
    "standalone"
    "standalone10"
    "tikz-uml"))
 :latex)

