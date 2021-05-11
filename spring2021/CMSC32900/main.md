---
abstract: |
  Most research in quantum computing today is performed against
  simulations of quantum computers rather than true quantum computers.
  Simulating a quantum computer entails implementing all of the unitary
  operators corresponding to the quantum gates as tensors. For high
  numbers of qubits, performing tensor multiplications for these
  simulations becomes quite expensive, since $N$-qubit gates correspond
  to $2^{N}$-dimensional tensors. One way to accelerate such a
  simulation is to use field programmable gate array (FPGA) hardware to
  efficiently compute the matrix multiplications. Though FPGAs can
  efficiently perform tensor multiplications, they are memory bound,
  having relatively small block random access memory. One way to
  potentially reduce the memory footprint of a quantum computing system
  is to represent it as a tensor network; tensor networks are a
  formalism for representing compositions of tensors wherein economical
  tensor contractions are readily identified. Thus we explore tensor
  networks as a means to reducing the memory footprint of quantum
  computing systems and broadly accelerating simulations of such
  systems.
author:
- Maksim Levental
bibliography:
- biblio.bib
title: Tensor Networks for Simulating Quantum Circuits on FPGAs
---

Introduction
============

Quantum computing (QC) refers to the manipulation and exploitation of
properties of quantum mechanical (QM) systems to perform computation. QM
systems exhibit properties such as superposition and entanglement and
clever *quantum algorithms* operate on these systems to perform general
computation. Unsurprisingly, the technique was intially conceived of as
a way to simulate physical systems themselves:

> "... \[N\]ature isn't classical, dammit, and if you want to make a
> simulation of nature, you'd better make it quantum mechanical, and by
> golly it's a wonderful problem, because it doesn't look so easy."

This closing remark from the keynote at the 1^st^ Physics of Computation
Conference in 1981, delivered by the late Richard Feynman
[@feynman1982simulating], succinctly, but accurately, expresses that
initial goal of quantum computing. Although modeling and simulating
physical systems on quantum computers remains a thriving area of
research we narrow our focus here to QC as it pertains to solving
general computational problems. Such problems include unstructured
search [@10.1145/237814.237866], integer factorization [@365700],
combinatorial optimization [@farhi2014quantum], and many others. It is
conjectured that some quantum algorithms enable quantum computers to
exceed the computational power of classical computers [@Zhong1460].

QC systems are composed of so-called quantum bits, or *qubits*, that
encode initial and intermediate states of computations. Transformations
between states are effected by time-reversible transforms, called
*unitary* *operators.* A formalism for representing quantum computation
is the *quantum circuit* formalism, where semenatically related
collections of $N$ qubits are represented as *registers* and
transformations are represented as *gates*, connected to those registers
by *wires*, and applied in sequence. As already mentioned, in hardware,
quantum circuits correspond to physical systems that readily exhibit
quantum mechnical properties; examples of physical qubits include
transmons, ion traps and topological quantum computers [@NAP25196].
Current state of the art QC systems are termed Noisy Intermediate-Scale
Quantum (NISQ) systems. Such systems are characterized by moderate
quantities of physical qubits (50-100) but relatively few logical qubits
(i.e. qubits robust to inteference and noise). Due to these limitations
(and, more broadly, the relative scarcity of functioning QC systems),
most research on quantum algorithms is performed with the assistance of
simulators of QC systems. Such simulators perform simulations by
representing $N$-qubit circuits as $2^{N}$-dimensional complex vectors
and transformations on those vectors as $2^{N}$-dimensional complex
matrix-vector multiplication. Naturally, due to this exponential growth,
naively executing such simulations quickly become infeasible for $N>50$
qubits [@pednault2020paretoefficient], both due to memory constraints
and compute time.

It's the case that matrices are a subclass of a more general
mathematical object called a *tensor* and composition of matrices can be
expressed as *tensor contraction*. *Tensor networks* (TNs) are
decompositions (i.e. factorizations) of very high-dimensional tensors
into networks (i.e. graphs) of low-dimensional tensors. TNs have been
successfullly employed in reducing the memory requirements of
simulations of QC systems [@pednault2020paretoefficient]. The critical
feature of tensor networks that make them useful for QC is the potential
to perform tensor contractions on the low-dimensional tensors in an
order such that, ultimately, the memory and compute time requirements
are lower than for the traditional representation. Existing applications
of TNs to quantum circuits focus primarily on memory constraints on
general purpose computers [@Fried_2018] and distributed environments
[@McCaskey_2018].

FPGAs are known to be performant for matrix multiplication uses cases
[@10.1145/3020078.3021740]. Though FPGAs typically run at lower clock
speeds (100-300MHz) than either conventional processors or even graphics
processors they, nonetheless, excel at latency constrained computations
owing to their fully "synchronous" nature (all modules in the same
*clock domain* execute simultaneously). At first glance FPGAs seem like
a suitable platform for performant simulation of quantum systems when
runtime is of the essence. Unfortunately, BRAM is one of the more
limited resources on an FPGA and therefore it becomes necessary to
explore memory reduction strategies for simulations (as well as runtime
reduction strategies). Hence, we explore tensor networks as a means of
reducing the memory footprint of quantum circuits with particular
attention to dimensions of the designs space as they pertain to
deployment to FPGAs.

The remainder of this report is organized as follows: section
[\[sec:Background\]](#sec:Background){reference-type="ref"
reference="sec:Background"} covers the necessary background wherein
subsection
[\[sec:Quantum-Circuits\]](#sec:Quantum-Circuits){reference-type="ref"
reference="sec:Quantum-Circuits"} very briefly reviews quantum
computation and quantum circuits (with particular focus on aspects that
will be relevant for tensor networks and FPGAs), section
[\[sec:Tensor-Networks\]](#sec:Tensor-Networks){reference-type="ref"
reference="sec:Tensor-Networks"} defines tensors and tensor networks
fairly rigorously and discusses algorithms for identifying optimal
contraction orders, section
[\[sec:FPGAs\]](#sec:FPGAs){reference-type="ref" reference="sec:FPGAs"}
discusses the constraints imposed by virtue of deploying to FPGA,
section
[\[sec:Implementation\]](#sec:Implementation){reference-type="ref"
reference="sec:Implementation"} describes our implementation of TNs on
FPGAs, section
[\[sec:Evaluation\]](#sec:Evaluation){reference-type="ref"
reference="sec:Evaluation"} reports our results on various random
circuits, and section
[\[sec:Conclusion\]](#sec:Conclusion){reference-type="ref"
reference="sec:Conclusion"} concludes with future research directions.

Background[\[sec:Background\]]{#sec:Background label="sec:Background"}
======================================================================

Quantum Computing[\[sec:Quantum-Circuits\]]{#sec:Quantum-Circuits label="sec:Quantum-Circuits"}
-----------------------------------------------------------------------------------------------

We very (very) quickly review quantum computing and quantum circuits as
they pertain to our project. For a much more pedagogically sound
introduction consult [@j2020quantum]. As already alluded to, quantum
computing exploits properties of quantum mechanical systems in order to
perform arbitrary computation. The fundamental unit of quantum
computation is a qubit, defined as two-dimensional quantum system with
state vector $\psi$ an element of a Hilbert space[^1] $H$:
$$\psi:=\alpha\begin{pmatrix}1\\
 0 
\end{pmatrix}+\beta\begin{pmatrix}0\\
 1 
\end{pmatrix}\equiv\begin{pmatrix}\alpha\\
 \beta 
\end{pmatrix}$$ where $\alpha,\beta\in\mathbb{\mathbb{C}}$ and
$\left|\alpha\right|^{2}+\left|\beta\right|^{2}=1$. This exhibits the
superposition property of the qubit[^2] in that the squares of the
coefficients are the probabilities of measuring the system in the
corresponding basis state. Collections of qubits have state vectors that
represented by the *tensor product* of the individual states of each
qubit; for example, two qubits $\psi,\phi$ have state vector
$$\psi\otimes\phi:=\begin{pmatrix}\alpha\\
 \beta 
\end{pmatrix}\otimes\begin{pmatrix}\alpha'\\
 \beta' 
\end{pmatrix}\equiv\begin{pmatrix}\alpha\alpha'\\
\alpha\beta'\\
\beta\alpha'\\
\beta\beta'
\end{pmatrix}$$ where the second $\otimes$ is the Kronecker product and
$\alpha\alpha'$ indicates conventional complex multiplication. Note that
the basis relative to which $\psi\otimes\phi$ is represented is the
standard basis for $\mathbb{C}^{4}$ and thus we observe exponential
growth in the size of the representation of an $N$-qubit system. An
alternative notation for state vectors is Dirac notation; for example,
for a single qubit $$\ket{\psi}\equiv\alpha\ket{0}+\beta\ket{1}$$ and a
2-qubit system $$\begin{aligned}
\ket{\psi}\otimes\ket{\phi} & \equiv\left(\alpha\ket{0}+\beta\ket{1}\right)\otimes\left(\alpha'\ket{0}+\beta'\ket{1}\right)\\
 & \equiv\alpha\alpha'\ket{0}\otimes\ket{0}+\alpha\beta'\ket{0}\otimes\ket{1}+\beta\alpha'\ket{1}\otimes\ket{0}+\beta\beta'\ket{1}\otimes\ket{1}\\
 & \equiv\alpha\alpha'\ket{0}\ket{0}+\alpha\beta'\ket{0}\ket{1}+\beta\alpha'\ket{1}\ket{0}+\beta\beta'\ket{1}\ket{1}\\
 & \equiv\alpha\alpha'\ket{00}+\alpha\beta'\ket{01}+\beta\alpha'\ket{10}+\beta\beta'\ket{11}\\
 & \equiv\alpha\alpha'\ket{0}+\alpha\beta'\ket{1}+\beta\alpha'\ket{2}+\beta\beta'\ket{3}\end{aligned}$$
where in the last line we've used the decimal representation for the bit
strings identifying the basis states. Of particular import for QC are
the *entangled* or *bell states*; they correspond to multi-qubit states,
such as
$$\ket{\xi}=\frac{1}{\sqrt{2}}\ket{00}+\frac{1}{\sqrt{2}}\ket{11}$$ that
cannot be "factored" into component states[^3]. Then, naturally, changes
in qubit states are represented as unitary[^4] matrices $U$; for example
$$\psi'=U\psi=\begin{pmatrix}U_{00} & U_{01}\\
U_{10} & U_{11}
\end{pmatrix}\begin{pmatrix}\alpha\\
 \beta 
\end{pmatrix}=\begin{pmatrix}U_{00}\alpha+U_{01}\beta\\
 U_{10}\alpha+U_{11}\beta 
\end{pmatrix}$$ Matrix representations of transformations on multi-qubit
states are constructed using the Kronecker product on the individual
matrix representations; for example

$$U\otimes V:=\begin{pmatrix}U_{00}V & U_{01}V\\ U_{10}V & U_{11}V \end{pmatrix}:=\begin{pmatrix}
 U_{00} V_{00} & U_{00} V_{01} & U_{01} V_{00} & U_{01} V_{01} \\
 U_{00} V_{10} & U_{00} V_{11} & U_{01} V_{10} & U_{01} V_{11} \\
 U_{10} V_{00} & U_{10} V_{01} & U_{11} V_{00} & U_{11} V_{01} \\
 U_{10} V_{10} & U_{10} V_{11} & U_{11} V_{10} & U_{11} V_{11}
\end{pmatrix}$$Here we see again an exponential growth in representation
size as a function of number of qubits.

& & & & &&\
& & & & & &\
& & & & & & &&&&

As already alluded to, quantum circuits are a formalism for representing
quantum computation in general and algorithms designed for quantum
computers in particular. In the quantum circuit formalism qubit states
are represented by wires and unitary transformations are represented by
gates (see figure
[\[fig:Quantum-Circuit-representing-1\]](#fig:Quantum-Circuit-representing-1){reference-type="ref"
reference="fig:Quantum-Circuit-representing-1"}), much like classical
combinational logic circuits might be, though, whereas combinational
logic is "memoryless"[^5], sequences of quantum gates specified by a
quantum circuit do in fact connote the evolution (in time) of the
qubits. In addition quantum gates, as opposed to classical gates, are
necessarily reversible and hence there are no quantum analogs to some
classical gates such as NOT and OR.

Tensors and Tensor Networks[\[sec:Tensor-Networks\]]{#sec:Tensor-Networks label="sec:Tensor-Networks"}
------------------------------------------------------------------------------------------------------

We quickly define tensors and tensor networks and then move on to tensor
network methods for simulating quantum circuits.

### Tensors

One definition of a tensor[^6] $T$ is as an element of a tensor product
space[^7]:
$$T\in\underbrace{V\otimes\cdots\otimes V}_{p{\text{ copies}}}\otimes\underbrace{V^{*}\otimes\cdots\otimes V^{*}}_{q{\text{ copies}}}$$
where $V^{*}$ is dual[^8] to $V$. Then $T$, in effect, acts a
multilinear map
$${\displaystyle T:\underbrace{V^{*}\times\dots\times V^{*}}_{p{\text{ copies}}}\times\underbrace{V\times\dots\times V}_{q{\text{ copies}}}\rightarrow\mathbb{R}}$$
by "applying" $p$ elements from $V$ to $p$ elements of $V^{*}$ and $q$
elements from $V^{*}$ to $q$ elements of $V$. Note the swapping of the
orders of $V,V^{*}$ in both the definitions and the description. $T$'s
coordinate basis representation

$${\displaystyle T\equiv T_{j_{1}\dots j_{q}}^{i_{1}\dots i_{p}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes\mathbf{e}^{j_{1}}\otimes\cdots\otimes\mathbf{e}^{j_{q}}}\label{eq:tensor_coord}$$
is determined by its evaluation on each set of bases

$${\displaystyle T_{j_{1}\dots j_{q}}^{i_{1}\dots i_{p}}:=T\left(\mathbf{e}^{i_{1}},\ldots,\mathbf{e}^{i_{p}},\mathbf{e}_{j_{1}},\ldots,\mathbf{e}_{j_{q}}\right)}$$
The pair $\left(p,q\right)$ is called the *type* or *valence* of **$T$**
while $\left(p+q\right)$ is the *order* of the tensor. **Note that we do
not use rank to mean either of these things**[^9]. Furthermore, eqn.
([\[eq:tensor\_coord\]](#eq:tensor_coord){reference-type="ref"
reference="eq:tensor_coord"}) in fact represents a linear sum of basis
elements, as it employs Einstein summation convention[^10]. Note we make
liberal use of summation convention in the following but occasionally
use explicit sums when it improves presentation (i.e. when we would like
to emphasize a particular contraction).

There are two important operations on tensors we need to define.
Firstly, we can form the tensor product $Z$ of two tensors $T,W$, of
types $\left(p,q\right),\left(r,s\right)$ respectively, to obtain a
tensor of type $\left(p+r,q+s\right)$: $$\begin{aligned}
Z & :=T\otimes W\\
 & \;=\left(T_{j_{1}\dots j_{q}}^{i_{1}\dots i_{p}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes{\mathbf{e}}^{j_{1}}\otimes\cdots\otimes{\mathbf{e}}^{j_{q}}\right)\otimes\left(W_{l_{1}\dots l_{s}}^{k_{1}\dots k_{r}}\;\mathbf{e}_{k_{1}}\otimes\cdots\otimes\mathbf{e}_{k_{r}}\otimes{\mathbf{e}}^{l_{1}}\otimes\cdots\otimes{\mathbf{e}}^{l_{s}}\right)\\
 & \;=\left(T_{j_{1}\dots j_{q}}^{i_{1}\dots i_{p}}W_{l_{1}\dots l_{s}}^{k_{1}\dots k_{r}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes\mathbf{e}_{k_{1}}\otimes\cdots\otimes\mathbf{e}_{k_{r}}\otimes{\mathbf{e}}^{j_{1}}\otimes\cdots\otimes{\mathbf{e}}^{j_{q}}\otimes{\mathbf{e}}^{l_{1}}\otimes\cdots\otimes{\mathbf{e}}^{l_{s}}\right)\\
 & :=Z_{j_{1}\dots j_{q+s}}^{i_{1}\dots i_{p+r}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{p+r}}\otimes{\mathbf{e}}^{j_{1}}\otimes\cdots\otimes{\mathbf{e}}^{j_{q+s}}\end{aligned}$$

Despite it being obvious, its important to note that the tensor product
$Z$ produces a tensor of order $\left(p+r+q+s\right)$, i.e. higher than
either of the operands. On the contrary, *tensor contraction* reduces
the order of a tensor. We define the contraction $Y$ of type
$\left(a,b\right)$ of a tensor $T$ to be the "pairing" of the $a$th and
$b$th bases: $$\begin{aligned}
Y & :=T_{j_{1}\dots j_{q}}^{i_{1}\dots i_{p}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{a-1}}\otimes\mathbf{e}_{i_{a+1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes\left(\mathbf{e}_{i_{a}}\cdot\mathbf{e}^{j_{b}}\right)\otimes\mathbf{e}^{j_{1}}\otimes\cdots\otimes\mathbf{e}^{j_{b-1}}\otimes\mathbf{e}^{j_{b+1}}\otimes\cdots\otimes\mathbf{e}^{j_{q}}\\
 & \;=T_{j_{1}\dots j_{q}}^{i_{1}\dots i_{p}}\delta_{i_{a}}^{j_{b}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{a-1}}\otimes\mathbf{e}_{i_{a+1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes\mathbf{e}^{j_{1}}\otimes\cdots\otimes\mathbf{e}^{j_{b-1}}\otimes\mathbf{e}^{j_{b+1}}\otimes\cdots\otimes\mathbf{e}^{j_{q}}\qquad\left(\text{since }\mathbf{e}_{i}\cdot\mathbf{e}^{j}=\delta_{i}^{j}\right)\\
 & \;=\sum_{j_{b}}T_{j_{1}\dots j_{b}\dots j_{q}}^{i_{1}\dots j_{b}\dots i_{p}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{a-1}}\otimes\mathbf{e}_{i_{a+1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes\mathbf{e}^{j_{1}}\otimes\cdots\otimes\mathbf{e}^{j_{b-1}}\otimes\mathbf{e}^{j_{b+1}}\otimes\cdots\otimes\mathbf{e}^{j_{q}}\\
 & :=Y_{j_{1}\dots i_{b-1}i_{b+1}\dots j_{q}}^{i_{1}\dots i_{a-1}i_{a+1}\dots i_{p}}\;\mathbf{e}_{i_{1}}\otimes\cdots\otimes\mathbf{e}_{i_{a-1}}\otimes\mathbf{e}_{i_{a+1}}\otimes\cdots\otimes\mathbf{e}_{i_{p}}\otimes\mathbf{e}^{j_{1}}\otimes\cdots\otimes\mathbf{e}^{j_{b-1}}\otimes\mathbf{e}^{j_{b+1}}\otimes\cdots\otimes\mathbf{e}^{j_{q}}\end{aligned}$$
where $\left(\cdot\right)$ means inner product. Notice that the order of
$Y$ is $\left(p-1,q-1\right)$. Finally notice that we can omit writing
out bases and just manipulate coordinates. We shall do as such when it
simplifies presentation.

As mentioned in the introduction, matrices can be represented as
tensors; for example, the two dimensional $N\times N$ matrix $M$ is
taken to be a tensor of type $\left(1,1\right)$ with basis
representation
$${\displaystyle M\equiv M_{j}^{i}\;\mathbf{e}_{i}\otimes\mathbf{e}^{j}}$$
where upper indices correspond to the row index and lower indices
correspond to the column index of the conventional matrix representation
and both range from $1$ to $N$. The attentive reader will notice that
the coordinate representation of the tensor product for type
$\left(1,1\right)$ tensors is exactly the Kronecker product for
matrices. Similarly, tensor contraction for type $\left(1,1\right)$
tensors is the familiar matrix trace:

$$M_{j}^{i}\left(\mathbf{e}_{i}\cdot\mathbf{e}^{j}\right)=M_{j}^{i}\delta_{i}^{j}=\sum_{i=1}^{N}M_{i}^{i}$$
More usefully, we can express matrix-vector multiplication in terms of
tensor contraction; let *$$\mathbf{x}:=\begin{pmatrix}x^{1}\\
 x^{2} 
\end{pmatrix}\equiv x^{1}\mathbf{e}_{1}+x^{2}\mathbf{e}_{2}\equiv x^{i}\mathbf{e}_{i}$$*
where we switch to valence index notation in the column vector for
closer affinity with tensor notation. Then it must be the case that
$$\mathbf{y}=M\mathbf{x}=\left(M_{j}^{i}\mathbf{e}_{i}\otimes\mathbf{e}^{j}\right)\left(x^{k}\mathbf{e}_{k}\right)=\left(M_{j}^{i}x^{k}\mathbf{e}_{i}\right)\left(\mathbf{e}^{j}\cdot\mathbf{e}_{k}\right)=M_{j}^{i}x^{k}\delta_{k}^{j}\mathbf{e}_{i}=M_{j}^{i}x^{j}\mathbf{e}_{i}$$
Letting $y^{i}:=M_{j}^{i}x^{j}$ we recognize conventional matrix-vector
multiplication. Employing tensor contraction in this way extends to
matrix-matrix multiplication (and tensor composition more broadly); for
two type $\left(1,1\right)$ tensors $M,L$ we can form the type
$\left(1,1\right)$ tensor $Z$ corresponding to matrix product $M\cdot L$
of $N\times N$ by first taking the tensor product

$$Z_{lj}^{ik}:=M_{l}^{i}L_{j}^{k}$$ The attentive reader will notice
that the coordinate representation of two tensors is exactly the
Kronecker product of two matrices. Then contracting along the off
diagonal
$$Z_{j}^{i}:=Z_{kj}^{ik}=M_{k}^{i}L_{j}^{k}\equiv\sum_{k=1}^{N}M_{k}^{i}L_{j}^{k}\label{eq:matrix_mult}$$
One can confirm that this is indeed conventional matrix multipliation of
two $N\times N$ matrices. In general, stated simply, when contracting
indices of a tensor product, contraction can be understood to be a sum
over shared indices.

### Tensor Networks

Tensor networks (TNs) are a way to factor tensors with large orders into
networks of tensors with lower orders; since the number of parameters a
tensor consists of is exponential in the order of the tensor, smaller
order tensors are much preferrable computationally. They were first used
to study ground states of one dimensional quantum many-body systems
[@PhysRevLett.69.2863] but have since been applied in other areas (such
as machine learning [@glasser2019expressive]). TNs lend themselves to a
diagrammatic representation which can be used to reason about such
factorizations (figure
[\[fig:Tensor-networks-demonstrating\]](#fig:Tensor-networks-demonstrating){reference-type="ref"
reference="fig:Tensor-networks-demonstrating"}). We will primarily be
interested in TNs as a means to factoring the state-vector of an
$N$-qubit system (see figure
[\[fig:State-vector-representation\]](#fig:State-vector-representation){reference-type="ref"
reference="fig:State-vector-representation"})
$$\ket{\psi}:=\sum_{i_{1}i_{2}\dots i_{N}}C^{i_{1}i_{2}\dots i_{N}}\ket{i_{1}}\ket{i_{2}}\cdots\ket{i_{N}}\label{eq:state_vector}$$
for which its common to propose an ansatz factorizations:

-   **Matrix Product States (MPS)** [@Kl_mper_1993], which yields
    factorization
    $$C^{i_{1}i_{2}\dots i_{N}}\equiv A_{j_{1}}^{i_{1}}A_{j_{2}}^{i_{1}j_{1}}\cdots A_{j_{N-1}}^{i_{N-1}j_{N-2}}A^{i_{N}j_{N-1}}$$
    where $j$ are called *bond indices.* If each index $i$ has dimension
    $d$ (i.e. takes on values 1 to $d$) then $C$ is specified by $d^{N}$
    parameters and can always be represented by an MPS factorization
    $Ndm^{2}$ parameters, where $m:=d^{N/2}$ is the bond dimension.
    While for this naive representation $d^{N}<Ndm^{2}$, in practice $m$
    is fixed to some moderate size such that $d^{N}>Ndm^{2}$ and the MPS
    factorization functions as an approximation.

-   **Projected Entangled Pair States (PEPS)** [@Verstraete:2004cf],
    which is a generalization of MPS to higher spatial dimensions, i.e.
    TNs that correspond to lattices of contractions of tensors, which
    themselves represent pairwise entangled quantum systems. Naturally,
    such a series of contractions doesn't lend itself to being expressed
    in traditional notation and thus we observe the power of tensor
    network diagrams (see PEPS in figure
    [\[fig:State-vector-factorization\]](#fig:State-vector-factorization){reference-type="ref"
    reference="fig:State-vector-factorization"}).

-   **Tree Tensor Networks (TTN)** [@PhysRevA.74.022320], a further
    generalization where tensors are entangled (and therefore
    contracted) hierarchically. In fact TTNs bear the closest
    resemblance to quantum circuits.

-   **Multi-scale Entanglement Renormalization Ansatz (MERA)**
    [@PhysRevLett.99.220405], a specific type of TTN where the tensors
    are alternatingly unitaries and isometries[^11].

### TNs for Simulating Quantum Circuits

Factoring eqn.
([\[eq:state\_vector\]](#eq:state_vector){reference-type="ref"
reference="eq:state_vector"}) is only the first step to successfully
simulating a quantum circuit. By representing some final state as a
tensor as well, and contracting across all indices (called *contracting
the network*), we can calculate the amplitude for that particular state.
Since tensor contraction is associative[^12], the order in which tensors
are actually contracted is a "hyperparameter" of TN methods; finding the
optimal contraction order, with respect to accuracy (assuming some
approximation has been made in constructing the factorization), compute
time, and memory requirements is critical.

In particular we focus on contraction orders for TTNs as they most
closely resemble quantum circuits. For a TTN consisting of $N$ tensors
(corresponding to $N$ gates) with maximum order $p$, worst case, we can
see that contraction time takes
$O\left(N\exp\left(O\left(p\right)\right)\right)$ since, in general,
contracting across all indices of a pair of tensors is exponential in
their orders[^13]. Markov et al. [@10.1137/050644756] showed that there
in fact exists a contraction ordering which results in a contraction
time of
$O\left(N^{O\left(1\right)}\exp\left(O\left(\operatorname{tw}\left(G^{L}\right)\right)\right)\right)$
where $G^{L}$ is the line graph[^14] of the tensor network and
$\operatorname{tw}\left(G^{L}\right)$ is the tree-width[^15] of $G^{L}$.

For quantum circuits consisting of many few qubit gates this technique
produces a much more (runtime) efficient evaluation of the circuit;
indeed Markov et al. further show that any TTN corresponding to a
quantum circuit with $N$ gates, where the number of gates that act on
any pair of qubits is bounded by $r$, has contraction time
$O\left(N^{O\left(1\right)}\exp\left(O\left(r\right)\right)\right)$.

Markov et al.'s results are not tight; their construction finds some
tree-decomposition with the correct corresponding tensor contraction
order that suits their aim (overall runtime complexity of the
translation from quantum circuit to TTN and the ultimate contraction).
In reality there are often contraction orders that are much more space
and runtime efficient. Though, in general problem is NP-hard
[@Arnborg87complexityof], for particular TTNs (corresponding to
circuits) there are heuristics, such as non-adjacent contractions
[@pednault2020paretoefficient], that produce more efficient orders.
Alternatively, randomized search and Bayesian optimization can be used
to identify efficient contraction orders [@Gray_2021; @Fried_2018].

FPGAs[\[sec:FPGAs\]]{#sec:FPGAs label="sec:FPGAs"}
--------------------------------------------------

![FPGA floorplan diagram
[@9103284].[\[fig:FPGA-floorplan-diagram\]]{#fig:FPGA-floorplan-diagram
label="fig:FPGA-floorplan-diagram"}](murra1-2998435.png){#fig:FPGA-floorplan-diagram
width="50%"}

A field-programmable gate array (FPGA) is a device designed to be
configured by a user into various arrangements of (classical) gates and
memory. FPGAs consist of arrays (hence the name) of configurable logic
blocks (CLBs), block ram (BRAM), and programmable busses that connect
CLBs and RAM into various topologies (see figure
[1](#fig:FPGA-floorplan-diagram){reference-type="ref"
reference="fig:FPGA-floorplan-diagram"}). The CLBs typically contain
arithmetic units (such as adders, multipliers, and accumulators) and
lookup tables (LUTs), that can be programmed to represent truth tables
for many boolean functions. Using hardware description languages (such
as VHDL or Verilog) designers specify modules and compose them into
circuits (also known as a *dataflows*) that perform arbitrary
computation. These circuits then go through a *place and route*
procedure before ultimately being instantiated on the FPGA as
*processing elements* (PEs) and connections between PEs.

While modules consisting purely of combinational logic compute their
outputs at the stated clock speed of the FPGA, inevitably I/O (i.e.
fetching data from memory) interleaved with such modules (otherwise
arranged into a pipeline architecture) creates pipeline stalls. Thus,
it's essential that FPGA designs are as compute bound as possible
(rather than I/O bound). In particular, we explore I/O minimal
generalized matrix multiplication (GEMM) [@10.1145/3373087.3375296] and
other *systolic array* architectures
[@10.1145/3431920.3439292; @genc2019gemmini]. A systolic architecture
[@1653825] is a gridded, pipelined, array of PEs that processes data as
the data flows[^16] through the array. Crucially, a systolic
architecture propagates partial results as well as input data through
the pipeline (see figure
[\[fig:systolic-array-2\]](#fig:systolic-array-2){reference-type="ref"
reference="fig:systolic-array-2"}). Systolic arrays are particularly
suited for I/O efficient matrix multiplication owing to the pipelining
of inputs (see figure
[\[fig:systolic-array\]](#fig:systolic-array){reference-type="ref"
reference="fig:systolic-array"}).

One remaining hurdle to simulating quantum compuations (i.e. carrying
out tensor contractions) on FPGAs is BRAM. The standard remediation is
to perform arithmetic with reduced precision[^17]. There is evidence
that suggests that simulations of quantum circuits, of varying depths
[@betelu2020limits], are robust to reduced precision computation as long
as that loss of precision is uncorrelated [@10.1145/3295500.3356155]
i.e. insofar as it can be treated as uncorrelated noise.

Implementation[\[sec:Implementation\]]{#sec:Implementation label="sec:Implementation"}
======================================================================================

We use quimb [@Gray2018] to specify quantum circuit and generate TNs
therefrom. We also use CoTenGra [@Gray_2021] to find optimal tensor
contraction orders. For deploying circuits to FPGAs we use Chisel
[@6241660] as a HDL, by way of an adaptation of the Gemmini systolic
array generator [@genc2019gemmini]. Notably we experiment with using
Gemmini as an accelerator (i.e. fully parameterizing the weights/entries
of the matrices) and "hardcoding" certain gates/tensors and routing data
instead. The advantage of the latter approach over the former is a
reduction in loads from memory for the weights. The success of the
approach depends heavily on whether certain sequences of fixed gates can
actually be pipelined in this way. We hypothesize that this might be the
case for low-depth circuits/TNs.

Evaluation[\[sec:Evaluation\]]{#sec:Evaluation label="sec:Evaluation"}
======================================================================

TODO

Conclusion[\[sec:Conclusion\]]{#sec:Conclusion label="sec:Conclusion"}
======================================================================

TODO

[^1]: A Hilbert space $H$ is a vector space augmented with an inner
    product such that, with respect to the metric induced by that inner
    product, all Cauchy sequences converge.

[^2]: We say that the qubit is in a superposition of the basis
    vectors/states.

[^3]: $\xi$ cannot be factored because there is no solution to the set
    of equations (for $\alpha,\alpha',\beta,\beta'$)
    $$\alpha\alpha'=\frac{1}{\sqrt{2}},\quad\alpha\beta'=0,\quad\beta\alpha'=0,\quad\beta\beta'=\frac{1}{\sqrt{2}}$$

[^4]: A matrix $U$ is unitary iff $UU^{\dagger}=U^{\dagger}U=I$, i.e. it
    is its own Hermitian conjugate or more simply if it is
    "self-inverse".

[^5]: The output of a combinational logic circuit at any time is only a
    function of the elements of the circuit and its inputs.

[^6]: There are several more at varying levels of mathematical
    sophistication. Chapter 14 of [@roman2007advanced] is the standard
    reference. Ironically, it is this author's opinion that one should
    shy away from physics oriented expositions on tensors.

[^7]: The collection of tensor products of elements of the component
    spaces quotiented by an equivalence relation.

[^8]: The dual space to a vector space $V$ is the vector $V^{*}$
    consisting of linear maps $f:V\rightarrow\mathbb{R}$. The dual basis
    of the dual space consists of $f_{i}$ such that
    $f_{i}\left(\mathbf{e}_{i}\right)=\delta_{ij}$. It is convention to
    write $f_{i}$ as $\mathbf{e}^{i}$ (note the superscript index).

[^9]: The *rank* of a tensor is the minimum number of distinct basis
    tensors necessary to define it; the tensor in eqn.
    ([\[eq:tensor\_coord\]](#eq:tensor_coord){reference-type="ref"
    reference="eq:tensor_coord"}) is in fact a rank 1 tensor. The
    definition is a generalization of the rank of a matrix (which,
    recalling, is the dimension of its column space, i.e. number of
    basis elements). Despite this obvious, reasonable definition for
    rank, one should be aware that almost all literature in this area of
    research uses rank to mean order.

[^10]: Repeated indices in juxtapose position indicate summation
    $a_{i}b^{i}:=\sum_{i}a[i]b[i]$.

[^11]: A tensor, seen as a multlinear map, that preserves distances
    under the ambient distance metric.

[^12]: This can be observed by noting that summing is an associative
    operation (or by analog with matrix-matrix multiplication).

[^13]: Consider contracting two $\left(1,1\right)$ tensors (as in eqn.
    ([\[eq:matrix\_mult\]](#eq:matrix_mult){reference-type="ref"
    reference="eq:matrix_mult"})), i.e. two order 2 tensors, which
    effectively is matrix multplication followed by trace. The
    complexity of this contraction is then
    $O\left(N^{2+1}+N\right)\equiv O\left(\exp\left(2\log N\right)\left(1+N\right)\right)$
    (where $N$ here is the characteristic dimension of the matrix).
    Assuming the ranges of all tensor indices is the same (i.e. $N$ is
    constant across all tensors), for example $N=2$ as in the case of
    matrices derived of unitary transformations operating on single
    qubits, we recover the stated complexity.

[^14]: A *line graph* captures edge adjacency; given a graph $G$,
    $G^{L}$ is defined such that each edge of $G$ corresponds to a
    vertex of $G^{L}$ and two vertices are are connected in $G^{L}$ if
    the edges in $G$ that they correspond to are adjacent on the same
    vertex (in $G$).

[^15]: A *tree decomposition* of a graph $G$ is a tree $T$ and a mapping
    from the vertices of $G$ into "bags" that satisfy the following
    properties

    1.  Each vertex must appear in at least one bag.

    2.  For each edge in $G$, at least one bag must contain both of the
        vertices it is adjacent on.

    3.  All bags containing a given vertex in $G$ must be connected in
        $T$.

    The width $w$ of a tree decomposition is the cardinality of the
    largest bag (minus one). Finally the *tree-width* of $G$ is the
    minimum width over all possible tree decompositions. Intuitively, a
    graph has low tree-width if it can be constructed by joining small
    graphs together into a tree.

[^16]: The relationship to cardiovascular "systolic" is in association
    with the flow of data into the array, akin to how blood flows
    through the veins into the human heart.

[^17]: Germaine to this issue is the fact that arithmetic on FPGAs is
    typically performed in fixed precision (via an integer
    representation), owing to higher compute cost incurred for floating
    point arithmetic.
