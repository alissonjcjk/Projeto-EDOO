import { useLocation, useNavigate } from 'react-router-dom'
import Sidebar from './Sidebar'

type Props = {
	children?: React.ReactNode
}

export default function Layout({ children }: Props) {
	const location = useLocation()
	const navigate = useNavigate()

	const handleNavigate = (path: string) => {
		navigate(path)
	}

	return (
		<div className="min-h-screen flex bg-gray-50">
			<Sidebar activePath={location.pathname} onNavigate={handleNavigate} />
			<main className="flex-1">{children}</main>
		</div>
	)
}

