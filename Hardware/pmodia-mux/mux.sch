<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S" xrefpart="/%S.%C%R">
<libraries>
<library name="con-hirose" urn="urn:adsk.eagle:library:152">
<description>&lt;b&gt;Hirose Connectors&lt;/b&gt;&lt;p&gt;
www.hirose.co.jp&lt;p&gt;
Include : &lt;br&gt;
con-hirose-df12d(3.0)60dp0.5v80.lbr from Bob Starr &amp;lt;rtzaudio@mindspring.com&amp;gt;&lt;br&gt;
con-hirose.lbr from Bob Starr &amp;lt;rtzaudio@mindspring.com&amp;gt;&lt;br&gt;</description>
<packages>
<package name="FH12-16S-0.5SH" urn="urn:adsk.eagle:footprint:7248/1" library_version="2">
<description>&lt;b&gt;0.5mm Pitch Connectors For FPC/FFC&lt;/b&gt;&lt;p&gt;
Source: &lt;a href= "http://www.hirose.co.jp/cataloge_hp/e58605370.pdf"&gt;Data sheet&lt;/a&gt;&lt;p&gt;</description>
<wire x1="-5.45" y1="0.5" x2="-5.95" y2="0.5" width="0.2032" layer="51"/>
<wire x1="-5.95" y1="0.5" x2="-5.95" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-5.95" y1="-0.5" x2="-5.45" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-5.45" y1="-0.5" x2="-5.45" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-5.45" y1="-1.9" x2="-5.15" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="-5.15" y1="-1.9" x2="-5.15" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-5.15" y1="-2.2" x2="-5.45" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-5.45" y1="-2.2" x2="-5.45" y2="-2.9" width="0.2032" layer="21"/>
<wire x1="5.45" y1="-2.9" x2="5.45" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="5.45" y1="-2.2" x2="5.15" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="5.15" y1="-2.2" x2="5.15" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.15" y1="-1.9" x2="5.45" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.45" y1="-1.9" x2="5.45" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="5.45" y1="-0.5" x2="5.95" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="5.95" y1="-0.5" x2="5.95" y2="0.5" width="0.2032" layer="51"/>
<wire x1="5.95" y1="0.5" x2="5.45" y2="0.5" width="0.2032" layer="51"/>
<wire x1="5.45" y1="0.5" x2="5.45" y2="2.5" width="0.2032" layer="51"/>
<wire x1="5.45" y1="2.5" x2="-5.45" y2="2.5" width="0.2032" layer="51"/>
<wire x1="-5.45" y1="2.5" x2="-5.45" y2="0.5" width="0.2032" layer="51"/>
<wire x1="5.15" y1="-1.9" x2="-5.15" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.45" y1="-2.9" x2="-5.45" y2="-2.9" width="0.2032" layer="21"/>
<wire x1="-5.45" y1="2.5" x2="-5.45" y2="1.5" width="0.2032" layer="21"/>
<wire x1="-4.25" y1="2.5" x2="-5.45" y2="2.5" width="0.2032" layer="21"/>
<wire x1="5.45" y1="1.5" x2="5.45" y2="2.5" width="0.2032" layer="21"/>
<wire x1="5.45" y1="2.5" x2="4.25" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5.45" y1="-1.5" x2="-5.45" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.45" y1="-1.9" x2="5.45" y2="-1.5" width="0.2032" layer="21"/>
<smd name="1" x="-3.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="2" x="-3.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="3" x="-2.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="4" x="-2.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="5" x="-1.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="6" x="-1.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="7" x="-0.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="8" x="-0.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="9" x="0.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="10" x="0.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="11" x="1.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="12" x="1.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="13" x="2.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="14" x="2.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="15" x="3.25" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="16" x="3.75" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<text x="-5.4476" y="4.095" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.2476" y="-0.3258" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.95" y1="2.55" x2="-3.55" y2="3.95" layer="29"/>
<rectangle x1="-3.875" y1="2.625" x2="-3.625" y2="3.875" layer="31"/>
<rectangle x1="-3.45" y1="2.55" x2="-3.05" y2="3.95" layer="29"/>
<rectangle x1="-3.375" y1="2.625" x2="-3.125" y2="3.875" layer="31"/>
<rectangle x1="-2.95" y1="2.55" x2="-2.55" y2="3.95" layer="29"/>
<rectangle x1="-2.875" y1="2.625" x2="-2.625" y2="3.875" layer="31"/>
<rectangle x1="-2.45" y1="2.55" x2="-2.05" y2="3.95" layer="29"/>
<rectangle x1="-2.375" y1="2.625" x2="-2.125" y2="3.875" layer="31"/>
<rectangle x1="-1.95" y1="2.55" x2="-1.55" y2="3.95" layer="29"/>
<rectangle x1="-1.875" y1="2.625" x2="-1.625" y2="3.875" layer="31"/>
<rectangle x1="-1.45" y1="2.55" x2="-1.05" y2="3.95" layer="29"/>
<rectangle x1="-1.375" y1="2.625" x2="-1.125" y2="3.875" layer="31"/>
<rectangle x1="-0.95" y1="2.55" x2="-0.55" y2="3.95" layer="29"/>
<rectangle x1="-0.875" y1="2.625" x2="-0.625" y2="3.875" layer="31"/>
<rectangle x1="-0.45" y1="2.55" x2="-0.05" y2="3.95" layer="29"/>
<rectangle x1="-0.375" y1="2.625" x2="-0.125" y2="3.875" layer="31"/>
<rectangle x1="0.05" y1="2.55" x2="0.45" y2="3.95" layer="29"/>
<rectangle x1="0.125" y1="2.625" x2="0.375" y2="3.875" layer="31"/>
<rectangle x1="0.55" y1="2.55" x2="0.95" y2="3.95" layer="29"/>
<rectangle x1="0.625" y1="2.625" x2="0.875" y2="3.875" layer="31"/>
<rectangle x1="1.05" y1="2.55" x2="1.45" y2="3.95" layer="29"/>
<rectangle x1="1.125" y1="2.625" x2="1.375" y2="3.875" layer="31"/>
<rectangle x1="1.55" y1="2.55" x2="1.95" y2="3.95" layer="29"/>
<rectangle x1="1.625" y1="2.625" x2="1.875" y2="3.875" layer="31"/>
<rectangle x1="2.05" y1="2.55" x2="2.45" y2="3.95" layer="29"/>
<rectangle x1="2.125" y1="2.625" x2="2.375" y2="3.875" layer="31"/>
<rectangle x1="2.55" y1="2.55" x2="2.95" y2="3.95" layer="29"/>
<rectangle x1="2.625" y1="2.625" x2="2.875" y2="3.875" layer="31"/>
<rectangle x1="3.05" y1="2.55" x2="3.45" y2="3.95" layer="29"/>
<rectangle x1="3.125" y1="2.625" x2="3.375" y2="3.875" layer="31"/>
<rectangle x1="3.55" y1="2.55" x2="3.95" y2="3.95" layer="29"/>
<rectangle x1="3.625" y1="2.625" x2="3.875" y2="3.875" layer="31"/>
<rectangle x1="4.75" y1="-1.1" x2="6.55" y2="1.1" layer="1" rot="R180"/>
<rectangle x1="4.7" y1="-1.175" x2="6.6" y2="1.175" layer="29" rot="R180"/>
<rectangle x1="4.825" y1="-1.025" x2="6.475" y2="1.025" layer="31" rot="R180"/>
<rectangle x1="-6.55" y1="-1.1" x2="-4.75" y2="1.1" layer="1" rot="R180"/>
<rectangle x1="-6.6" y1="-1.175" x2="-4.7" y2="1.175" layer="29" rot="R180"/>
<rectangle x1="-6.475" y1="-1.025" x2="-4.825" y2="1.025" layer="31" rot="R180"/>
<rectangle x1="-3.85" y1="2.55" x2="-3.65" y2="3.4" layer="51"/>
<rectangle x1="-3.35" y1="2.55" x2="-3.15" y2="3.4" layer="51"/>
<rectangle x1="-2.85" y1="2.55" x2="-2.65" y2="3.4" layer="51"/>
<rectangle x1="-2.35" y1="2.55" x2="-2.15" y2="3.4" layer="51"/>
<rectangle x1="-1.85" y1="2.55" x2="-1.65" y2="3.4" layer="51"/>
<rectangle x1="-1.35" y1="2.55" x2="-1.15" y2="3.4" layer="51"/>
<rectangle x1="-0.85" y1="2.55" x2="-0.65" y2="3.4" layer="51"/>
<rectangle x1="-0.35" y1="2.55" x2="-0.15" y2="3.4" layer="51"/>
<rectangle x1="0.15" y1="2.55" x2="0.35" y2="3.4" layer="51"/>
<rectangle x1="0.65" y1="2.55" x2="0.85" y2="3.4" layer="51"/>
<rectangle x1="1.15" y1="2.55" x2="1.35" y2="3.4" layer="51"/>
<rectangle x1="1.65" y1="2.55" x2="1.85" y2="3.4" layer="51"/>
<rectangle x1="2.15" y1="2.55" x2="2.35" y2="3.4" layer="51"/>
<rectangle x1="2.65" y1="2.55" x2="2.85" y2="3.4" layer="51"/>
<rectangle x1="3.15" y1="2.55" x2="3.35" y2="3.4" layer="51"/>
<rectangle x1="3.65" y1="2.55" x2="3.85" y2="3.4" layer="51"/>
<polygon width="0.2032" layer="21">
<vertex x="-3.95" y="-2.2"/>
<vertex x="-3.75" y="-2.6"/>
<vertex x="-3.55" y="-2.2"/>
</polygon>
</package>
</packages>
<packages3d>
<package3d name="FH12-16S-0.5SH" urn="urn:adsk.eagle:package:7319/1" type="box" library_version="2">
<description>0.5mm Pitch Connectors For FPC/FFC
Source: Data sheet</description>
<packageinstances>
<packageinstance name="FH12-16S-0.5SH"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PINV" urn="urn:adsk.eagle:symbol:7169/1" library_version="2">
<wire x1="0" y1="0.254" x2="0" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="0" y1="-0.254" x2="1.016" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-0.254" x2="1.27" y2="0.254" width="0.1524" layer="94"/>
<wire x1="1.27" y1="0.254" x2="0" y2="0.254" width="0.1524" layer="94"/>
<text x="2.032" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="PIN" urn="urn:adsk.eagle:symbol:7167/1" library_version="2">
<wire x1="0" y1="0.254" x2="0" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="0" y1="-0.254" x2="1.016" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-0.254" x2="1.27" y2="0.254" width="0.1524" layer="94"/>
<wire x1="1.27" y1="0.254" x2="0" y2="0.254" width="0.1524" layer="94"/>
<text x="2.032" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FH12-16S-0.5S" urn="urn:adsk.eagle:component:7384/2" prefix="X" library_version="2">
<description>&lt;b&gt;0.5mm Pitch Connectors For FPC/FFC&lt;/b&gt;&lt;p&gt;
Source: &lt;a href= "http://www.hirose.co.jp/cataloge_hp/e58605370.pdf"&gt;Data sheet&lt;/a&gt;&lt;p&gt;</description>
<gates>
<gate name="-1" symbol="PINV" x="0" y="17.78" addlevel="always"/>
<gate name="-2" symbol="PIN" x="0" y="15.24" addlevel="always"/>
<gate name="-3" symbol="PIN" x="0" y="12.7" addlevel="always"/>
<gate name="-4" symbol="PIN" x="0" y="10.16" addlevel="always"/>
<gate name="-5" symbol="PIN" x="0" y="7.62" addlevel="always"/>
<gate name="-6" symbol="PIN" x="0" y="5.08" addlevel="always"/>
<gate name="-7" symbol="PIN" x="0" y="2.54" addlevel="always"/>
<gate name="-8" symbol="PIN" x="0" y="0" addlevel="always"/>
<gate name="-9" symbol="PIN" x="0" y="-2.54" addlevel="always"/>
<gate name="-10" symbol="PIN" x="0" y="-5.08" addlevel="always"/>
<gate name="-11" symbol="PIN" x="0" y="-7.62" addlevel="always"/>
<gate name="-12" symbol="PIN" x="0" y="-10.16" addlevel="always"/>
<gate name="-13" symbol="PIN" x="0" y="-12.7" addlevel="always"/>
<gate name="-14" symbol="PIN" x="0" y="-15.24" addlevel="always"/>
<gate name="-15" symbol="PIN" x="0" y="-17.78" addlevel="always"/>
<gate name="-16" symbol="PIN" x="0" y="-20.32" addlevel="always"/>
</gates>
<devices>
<device name="H" package="FH12-16S-0.5SH">
<connects>
<connect gate="-1" pin="1" pad="1"/>
<connect gate="-10" pin="1" pad="10"/>
<connect gate="-11" pin="1" pad="11"/>
<connect gate="-12" pin="1" pad="12"/>
<connect gate="-13" pin="1" pad="13"/>
<connect gate="-14" pin="1" pad="14"/>
<connect gate="-15" pin="1" pad="15"/>
<connect gate="-16" pin="1" pad="16"/>
<connect gate="-2" pin="1" pad="2"/>
<connect gate="-3" pin="1" pad="3"/>
<connect gate="-4" pin="1" pad="4"/>
<connect gate="-5" pin="1" pad="5"/>
<connect gate="-6" pin="1" pad="6"/>
<connect gate="-7" pin="1" pad="7"/>
<connect gate="-8" pin="1" pad="8"/>
<connect gate="-9" pin="1" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:7319/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="FH12-16S-0.5SH(55)" constant="no"/>
<attribute name="OC_FARNELL" value="1324546" constant="no"/>
<attribute name="OC_NEWARK" value="34M6162" constant="no"/>
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pad">
<packages>
<package name="PAD">
<smd name="P$1" x="0" y="0" dx="0.635" dy="0.635" layer="1" roundness="100"/>
</package>
</packages>
<symbols>
<symbol name="PAD">
<pin name="P$1" x="0" y="0" length="middle"/>
<circle x="0" y="0" radius="2.54" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PAD">
<gates>
<gate name="G$1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="PAD" package="PAD">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="X1" library="con-hirose" library_urn="urn:adsk.eagle:library:152" deviceset="FH12-16S-0.5S" device="H" package3d_urn="urn:adsk.eagle:package:7319/1"/>
<part name="U$1" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$2" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$3" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$4" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$5" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$6" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$7" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$8" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$9" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$10" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$11" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$12" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$13" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$14" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$15" library="pad" deviceset="PAD" device="PAD"/>
<part name="U$16" library="pad" deviceset="PAD" device="PAD"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="X1" gate="-1" x="109.22" y="73.66" smashed="yes">
<attribute name="NAME" x="111.252" y="72.898" size="1.778" layer="95"/>
<attribute name="VALUE" x="106.68" y="76.2" size="1.778" layer="96"/>
</instance>
<instance part="X1" gate="-2" x="109.22" y="71.12" smashed="yes">
<attribute name="NAME" x="111.252" y="70.358" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-3" x="109.22" y="68.58" smashed="yes">
<attribute name="NAME" x="111.252" y="67.818" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-4" x="109.22" y="66.04" smashed="yes">
<attribute name="NAME" x="111.252" y="65.278" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-5" x="109.22" y="63.5" smashed="yes">
<attribute name="NAME" x="111.252" y="62.738" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-6" x="109.22" y="60.96" smashed="yes">
<attribute name="NAME" x="111.252" y="60.198" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-7" x="109.22" y="58.42" smashed="yes">
<attribute name="NAME" x="111.252" y="57.658" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-8" x="109.22" y="55.88" smashed="yes">
<attribute name="NAME" x="111.252" y="55.118" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-9" x="109.22" y="53.34" smashed="yes">
<attribute name="NAME" x="111.252" y="52.578" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-10" x="109.22" y="50.8" smashed="yes">
<attribute name="NAME" x="111.252" y="50.038" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-11" x="109.22" y="48.26" smashed="yes">
<attribute name="NAME" x="111.252" y="47.498" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-12" x="109.22" y="45.72" smashed="yes">
<attribute name="NAME" x="111.252" y="44.958" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-13" x="109.22" y="43.18" smashed="yes">
<attribute name="NAME" x="111.252" y="42.418" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-14" x="109.22" y="40.64" smashed="yes">
<attribute name="NAME" x="111.252" y="39.878" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-15" x="109.22" y="38.1" smashed="yes">
<attribute name="NAME" x="111.252" y="37.338" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-16" x="109.22" y="35.56" smashed="yes">
<attribute name="NAME" x="111.252" y="34.798" size="1.778" layer="95"/>
</instance>
<instance part="U$1" gate="G$1" x="71.12" y="88.9" smashed="yes"/>
<instance part="U$2" gate="G$1" x="71.12" y="83.82" smashed="yes"/>
<instance part="U$3" gate="G$1" x="71.12" y="78.74" smashed="yes"/>
<instance part="U$4" gate="G$1" x="71.12" y="73.66" smashed="yes"/>
<instance part="U$5" gate="G$1" x="71.12" y="68.58" smashed="yes"/>
<instance part="U$6" gate="G$1" x="71.12" y="63.5" smashed="yes"/>
<instance part="U$7" gate="G$1" x="71.12" y="58.42" smashed="yes"/>
<instance part="U$8" gate="G$1" x="71.12" y="53.34" smashed="yes"/>
<instance part="U$9" gate="G$1" x="71.12" y="48.26" smashed="yes"/>
<instance part="U$10" gate="G$1" x="71.12" y="43.18" smashed="yes"/>
<instance part="U$11" gate="G$1" x="71.12" y="38.1" smashed="yes"/>
<instance part="U$12" gate="G$1" x="71.12" y="33.02" smashed="yes"/>
<instance part="U$13" gate="G$1" x="71.12" y="27.94" smashed="yes"/>
<instance part="U$14" gate="G$1" x="71.12" y="22.86" smashed="yes"/>
<instance part="U$15" gate="G$1" x="71.12" y="17.78" smashed="yes"/>
<instance part="U$16" gate="G$1" x="71.12" y="12.7" smashed="yes"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P$1"/>
<wire x1="88.9" y1="88.9" x2="71.12" y2="88.9" width="0.1524" layer="91"/>
<wire x1="88.9" y1="88.9" x2="88.9" y2="73.66" width="0.1524" layer="91"/>
<pinref part="X1" gate="-1" pin="1"/>
<wire x1="88.9" y1="73.66" x2="106.68" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="X1" gate="-2" pin="1"/>
<wire x1="106.68" y1="71.12" x2="86.36" y2="71.12" width="0.1524" layer="91"/>
<wire x1="86.36" y1="71.12" x2="86.36" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P$1"/>
<wire x1="86.36" y1="83.82" x2="71.12" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="78.74" x2="83.82" y2="78.74" width="0.1524" layer="91"/>
<wire x1="83.82" y1="78.74" x2="83.82" y2="68.58" width="0.1524" layer="91"/>
<pinref part="X1" gate="-3" pin="1"/>
<wire x1="83.82" y1="68.58" x2="106.68" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="73.66" x2="81.28" y2="73.66" width="0.1524" layer="91"/>
<wire x1="81.28" y1="73.66" x2="81.28" y2="66.04" width="0.1524" layer="91"/>
<pinref part="X1" gate="-4" pin="1"/>
<wire x1="81.28" y1="66.04" x2="106.68" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="68.58" x2="78.74" y2="68.58" width="0.1524" layer="91"/>
<wire x1="78.74" y1="68.58" x2="78.74" y2="63.5" width="0.1524" layer="91"/>
<pinref part="X1" gate="-5" pin="1"/>
<wire x1="78.74" y1="63.5" x2="106.68" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$7" gate="G$1" pin="P$1"/>
<pinref part="X1" gate="-7" pin="1"/>
<wire x1="71.12" y1="58.42" x2="106.68" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="X1" gate="-9" pin="1"/>
<wire x1="106.68" y1="53.34" x2="78.74" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U$9" gate="G$1" pin="P$1"/>
<wire x1="78.74" y1="53.34" x2="78.74" y2="48.26" width="0.1524" layer="91"/>
<wire x1="78.74" y1="48.26" x2="71.12" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="X1" gate="-10" pin="1"/>
<wire x1="106.68" y1="50.8" x2="81.28" y2="50.8" width="0.1524" layer="91"/>
<wire x1="81.28" y1="50.8" x2="81.28" y2="43.18" width="0.1524" layer="91"/>
<pinref part="U$10" gate="G$1" pin="P$1"/>
<wire x1="81.28" y1="43.18" x2="71.12" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="X1" gate="-11" pin="1"/>
<wire x1="106.68" y1="48.26" x2="83.82" y2="48.26" width="0.1524" layer="91"/>
<wire x1="83.82" y1="48.26" x2="83.82" y2="38.1" width="0.1524" layer="91"/>
<pinref part="U$11" gate="G$1" pin="P$1"/>
<wire x1="83.82" y1="38.1" x2="71.12" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="X1" gate="-12" pin="1"/>
<wire x1="106.68" y1="45.72" x2="86.36" y2="45.72" width="0.1524" layer="91"/>
<wire x1="86.36" y1="45.72" x2="86.36" y2="33.02" width="0.1524" layer="91"/>
<pinref part="U$12" gate="G$1" pin="P$1"/>
<wire x1="86.36" y1="33.02" x2="71.12" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="X1" gate="-13" pin="1"/>
<wire x1="106.68" y1="43.18" x2="88.9" y2="43.18" width="0.1524" layer="91"/>
<wire x1="88.9" y1="43.18" x2="88.9" y2="27.94" width="0.1524" layer="91"/>
<pinref part="U$13" gate="G$1" pin="P$1"/>
<wire x1="88.9" y1="27.94" x2="71.12" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$14" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="22.86" x2="91.44" y2="22.86" width="0.1524" layer="91"/>
<wire x1="91.44" y1="22.86" x2="91.44" y2="40.64" width="0.1524" layer="91"/>
<pinref part="X1" gate="-14" pin="1"/>
<wire x1="91.44" y1="40.64" x2="106.68" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="X1" gate="-15" pin="1"/>
<wire x1="106.68" y1="38.1" x2="93.98" y2="38.1" width="0.1524" layer="91"/>
<wire x1="93.98" y1="38.1" x2="93.98" y2="17.78" width="0.1524" layer="91"/>
<pinref part="U$15" gate="G$1" pin="P$1"/>
<wire x1="93.98" y1="17.78" x2="71.12" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$16" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="12.7" x2="99.06" y2="12.7" width="0.1524" layer="91"/>
<pinref part="X1" gate="-16" pin="1"/>
<wire x1="99.06" y1="12.7" x2="99.06" y2="35.56" width="0.1524" layer="91"/>
<wire x1="99.06" y1="35.56" x2="106.68" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="X1" gate="-6" pin="1"/>
<wire x1="106.68" y1="60.96" x2="76.2" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P$1"/>
<wire x1="76.2" y1="60.96" x2="76.2" y2="63.5" width="0.1524" layer="91"/>
<wire x1="76.2" y1="63.5" x2="71.12" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="X1" gate="-8" pin="1"/>
<wire x1="106.68" y1="55.88" x2="76.2" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="P$1"/>
<wire x1="76.2" y1="55.88" x2="76.2" y2="53.34" width="0.1524" layer="91"/>
<wire x1="76.2" y1="53.34" x2="71.12" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
