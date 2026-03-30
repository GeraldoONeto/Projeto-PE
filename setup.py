from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
    "recomendador",
    ["recomendacao.cpp", "similaridade.cpp", "solver.cpp"],
    cxx_std = 17
    ), 
]

setup(
    name="recomendador",
    version="0.1.0",
    description="Algoritmo de recomendação",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False, 
)