高铁轮轨姿态反映了车轮与钢轨之间复杂的动态相互作用和约束关系，掌握他们之间真实接触姿态是保障高速铁路安全运营的重要基础。如何能够精确获得高铁轮轨姿态一直是国内铁路科研的热门研究领域。而单单从二维图像上获取轮轨接触姿态是不精确、不可靠的，需要将轮轨表面的特征点提取出来，重建出一个三维模型才能更加真实正确地获得轮轨接触姿态。

高铁列车运行速度快，轮轨表面相对光滑且无明显特征点，使得特征不易提取，点云重建精度较差，给三维重建带来了很大的困难。

<div class="imgs" align="center" ><img src="http://static.zybuluo.com/TangWill/83s2b1jh93zumwaeavyhn0w2/00.gif" alt="01" width="45%" height="45%"/></div>

针对高铁列车速度快的特点，可以通过采用非接触的测量方法 —— 计算机视觉。物体表面的点云三维重建在机器视觉领域已经成为一个很重要的研究方向。点云即物体表面特征点的集合，这些点包含了物体表面的三维坐标以及颜色等信息。点云的重建方法包括基于结构光的三维重建技术、光照模型、基于单目视觉或双目视觉的重建方法等。

当物体表面相对光滑时，物体的特征不易提取，点云重建精度较差。而基于编码结构光的重建方法可以向物体表面投射编码图案从而增加物体表面的特征，获得较好的点云重建结果。编码结构光三维重建技术主要由图像获取、结构光编码、结构光解码、系统标定和三维坐标计算等5个关键技术组成。

结构光的编码方式主要有时间编码和空间编码两种。时间编码虽具有较好的重建精度，但由于需要向物体表面投射多张图片，所以对于运动物体来说时间编码的结构光重建不是一个好的选择.空间编码虽然重建精度相对没有时间编码好，但由于只需投射一张图片，所以常常用于动态物体的物体重建。综上所述，本项目主要研究通过空间编码的方式获得相对更高精度和高密度的三维点云。

项目前期，对项目研究内容进行深入了解，根据研究内容查阅相关文献资料，了解了目前各项技术研究现状，能够明白经典方法的原理并能够将其实现。在学习并理解了研究内容及相关原理的基础上，对空间编码中的基于 De Bruijn 序列编码和基于伪随机矩阵编码两种方式的有关理论及其相关论文进行了学习，部分论文如下所示。

<div class="imgs" align="center" ><img src="http://static.zybuluo.com/TangWill/epo24nprhgogp1g0s38hiwy7/02.png" alt="03" width="30%" height="30%" />                <img src="http://static.zybuluo.com/TangWill/6q8x3x920nxdyluimu43gut1/03.png" alt="04" width="30%" height="30%" /> <img src="http://static.zybuluo.com/TangWill/z6giu9sqibq08fc1crweplxa/04.png" alt="05" width="30%" height="30%"  /></div>

项目中期，对前期所阅读的文献和经典算法的实现进行研究、归纳、整理。参照本项目的研究内容拟选出适用的相关算法与技术，提出实验思路，制定实验方案。

伪随机序列具有良好的窗口特性，即通过一个较小的窗口在编码图案上面移动时，每个窗口内的编码组合是唯一的，根据窗口的这个特性可以唯一地辨识编码图案上的特征点。复现论文的本原多项式采用 h(x)=2𝑥^6+2𝑥^5+𝑥^4+3𝑥^3+2𝑥^2+2𝑥+1，菱形作为结构光编码图案的基本元素，红、蓝、绿、黑四种颜色作为标记菱形代表的不同数值，窗口大小为$2\times 3$，同时以菱形角点作为特征点，可以有效提高特征点提取的精度。根据论文提出的结构光解码方法，可有效提取物体表面特征点，但由于角点数量较少，不能达到稠密点云的效果，未来可以通过改善相机分辨率，减小菱形面积，增加特征点等方式以提高特征点的密度。部分参考论文和实验结果如下。

<div class="imgs" align="center" ><img src="http://static.zybuluo.com/TangWill/z6giu9sqibq08fc1crweplxa/04.png" alt="06" width="22%" height="22%" />                <img src="http://static.zybuluo.com/TangWill/9jljaktk7e3qso61by60pohf/05.png" alt="07" width="22%" height="22%" /> <img src="http://static.zybuluo.com/TangWill/1wqxgxn4iwdicq1v9rs04e1x/06.png" alt="08" width="22%" height="22%"  /><img src="http://static.zybuluo.com/TangWill/s3gah640whmsbfxoxzg2pqib/07.png" alt="09" width="22%" height="22%"  /></div>

http://tang5618.com/data/video/00.mp4

De Bruijn 序列由n种不同元素构成，任意长度为m的连续子序列只出现一次。复现的论文以 B(3,4) 序列进行编码，条纹作为结构光编码图案的基本元素，红、蓝、绿三种颜色作为标记条纹代表的不同数值，窗口大小为 4*1，以条纹中心点作为特征点。同时在 HSV 颜色空间模型中，以余弦函数对条纹的 V 通道进行编码。在结构光解码时，除了提取条纹中心点作为特征点，同时对拍摄到的图像的 V 通道进行加窗傅里叶变换分析，通过分析得到的相位进而增加特征点的密度。根据论文的基本思路，可在提高提取点云进度的同时增加点云的稠密度，实验效果较好。根据项目内容和有关研究的进展，在研究论文和实验的基础上，对复现论文的算法进行改进，提出适合项目场景的算法流程。部分论文如下。

<div class="imgs" align="center" ><img src="http://static.zybuluo.com/TangWill/i9bvx3xay0c8v4040hjzulcv/08.png" alt="10" width="22%" height="22%" />                <img src="http://static.zybuluo.com/TangWill/wspx83923ujobnjysj4y2l3h/09.png" alt="11" width="22%" height="22%" /> <img src="http://static.zybuluo.com/TangWill/pflvpf9yzwkfw8csn0at2trl/10.png" alt="12" width="22%" height="22%"  /><img src="http://static.zybuluo.com/TangWill/v0cdilgqhy1k4oqaw2dhdpgh/11.png" alt="13" width="22%" height="22%"  /></div>

基于改进的算法对球体表面进行重建，得到约 17W 条点云数据，在 Meshlab 中对点云数据进行渲染，实验结果如下。
<div class="imgs" align="center" ><img src="http://static.zybuluo.com/TangWill/etw2k42uqvbb63zyvbry0ki6/13.png" alt="14" /></div>

改用以 B(4,3) 序列进行编码，条纹作为结构光编码图案的基本元素，红、蓝、绿、白四种颜色作为标记条纹代表的不同数值，窗口大小为 3*1，以条纹中心点作为特征点。同样对球体表面进行重建，得到约 20W 条点云数据，在 Meshlab 中对点云数据进行渲染，实验结果如下。

<div class="imgs" align="center" ><img src="http://static.zybuluo.com/TangWill/8z4qxmk5467d6r7rpr1brpkg/14.png" alt="15" /></div>

项目于2019年4月立项，研究至今，基本遵循研究计划，对部分现有的基于空间编码结构光的三维重建方法进行了研究、实现和调优，根据现有算法和项目应用场景提出了自己的解决方案，并完成了软件的封装，预期可用于静态和运动物体的三维重建。

- 亚像素级条纹中心的提取：设计了编码图案及适用的条纹中心提取算法，可精确到亚像素级别
- 小波变换增加点云稠密度：用基于广义 Morse 小波的小波变换获取条纹相位，增加点云稠密度
- 构建三维重建全流程平台：将上述算法与点云可视化封装成软件，预期可用于轮轨姿态三维重建

软件展示如下：

http://tang5618.com/data/video/02.mp4

最后，对项目的技术和成果进行一个简单的 <a href="http://tang5618.com/data/pdf/wordpress/tq.pdf">总结</a>。

---

 本项目的介绍也可以访问  [这里](https://tang5618.com/wordpress/?p=598)
