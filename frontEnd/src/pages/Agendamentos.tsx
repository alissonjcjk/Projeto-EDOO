export default function AgendamentosPage() {
	const openNovoAgendamento = () => {
		// TODO: abrir modal de novo agendamento
		console.log('Abrir modal: Novo Agendamento')
	}

	return (
		<div className="p-6">
			<div className="flex items-center justify-between mb-2">
				<div>
					<h1 className="text-3xl font-semibold">Agendamentos</h1>
					<p className="text-xl text-gray-600">Gerencie todos os agendamentos da barbearia</p>
				</div>

				<div>
					<button
						onClick={openNovoAgendamento}
						className="inline-flex items-center gap-2 bg-red-600 hover:bg-red-700 text-white font-semibold px-4 py-2 rounded shadow"
						aria-label="Novo Agendamento"
					>
						+ Novo Agendamento
					</button>
				</div>
			</div>

			{/* conteúdo da página vai aqui */}
		</div>
	)
}
