Pod::Spec.new do |s|
	s.name                = "mob_linksdk_pro_pure"

	s.version             = "0.0.2"

	s.summary             = 'moblinkpro纯净版，无SDK版本，mob.com网页一键唤醒App并到达指定内页SDK,原Pod名称为:MobLink,请知悉～'
	s.license             = 'Copyright © 2012-2017 mob.com'
	s.author              = { "MobProducts" => "mobproducts@163.com" }
	s.homepage            = 'http://www.mob.com'

	s.source              = { :git => 'https://github.com/MobClub/MobLinkPro-Pure-for-IOS.git',:tag => s.version.to_s}
    
	s.platform            = :ios, '8.0'
	s.frameworks          = "ImageIO", "JavaScriptCore"
	s.libraries           = "icucore", "z", "c++", "sqlite3"
	s.vendored_frameworks = 'MobLinkPro.framework'
	s.dependency 'mobfoundation_spec'
end
